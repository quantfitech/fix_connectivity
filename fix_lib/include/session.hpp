#ifndef SESSION_HPP
#define SESSION_HPP

#include "session_options.hpp"
#include "session_state.hpp"
#include "writer.hpp"
#include "timer.hpp"
#include "connection_interface.hpp" 
#include "event_manager_interface.hpp"
#include "utils.hpp"
#include "fix_message.hpp"
#include "tag.hpp"
#include "session_options.hpp"
#include "version_selector.hpp"
#include "logger.hpp"
#include "base64_hmac.h"
#include "fix_values.hpp"
#include <map>
#include <set>


namespace qffixlib
{
    using namespace qfapp;

    namespace encode_options {
        constexpr int none               = 0b00000;
        constexpr int set_checksum       = 0b00001;
        constexpr int set_body_length    = 0b00010;
        constexpr int set_begin_string   = 0b00100;
        constexpr int set_msg_seq_num    = 0b01000;
        constexpr int set_sending_time   = 0b10000;
        constexpr int standard           = set_checksum | set_body_length | set_begin_string | set_msg_seq_num | set_sending_time;
        constexpr int standard_no_sending = set_checksum | set_body_length | set_begin_string | set_msg_seq_num;
    }

    constexpr std::array<char,8> SessionMessages = {'0', '1', '2', '3', '4', '5', 'A', '\x01'};

    template<Version V>
    class Session : public ConnectionInterface
    {
        using Logon = typename VersionSelector<V>::Logon;
        using Reject = typename VersionSelector<V>::Reject;
        using Logout = typename VersionSelector<V>::Logout;
        using Heartbeat = typename VersionSelector<V>::Heartbeat;
        using SequenceReset = typename VersionSelector<V>::SequenceReset;
        using ResendRequest = typename VersionSelector<V>::ResendRequest;
        using TestRequest = typename VersionSelector<V>::TestRequest;

        //using Header = typename VersionSelector<V>::Header

        public:
       
        Session(std::shared_ptr<EventManagerInterface> event_manager)
        : mEventManagerInterface(event_manager) {
            beginString(std::string(VersionSelector<V>::VERSION_STR.data(), VersionSelector<V>::VERSION_STR.size()));
        }

        void setWriter(std::shared_ptr<Writer> writer)
        {
            mWriter = writer;
        }

        bool isSessionMessage(const MsgChars& msgType) {
            auto it = std::find(SessionMessages.begin(), SessionMessages.end(), msgType[0]);
            return it != SessionMessages.end();
        }

        void flushBufferedMessages() {
             for (auto it = mQueuedMessages.begin(); it != mQueuedMessages.end();) {
                TokenIterator iter(it->second.data(), it->second.length());
                while(iter->tag != 35) {
                    ++iter;
                }
                MsgChars msgType;
                if (iter->length == 1) {
                    msgType[0] = *(iter->data);
                    msgType[1] = '\n';
                } else if (iter->length == 2) {
                    msgType[0] = *(iter->data);
                    msgType[1] = *(iter->data+1);
                } else {
                    throw std::runtime_error("unexpected messagetype, length {}" + std::to_string(iter->length));
                }
                if (!isSessionMessage(msgType)) {
                   onMessage(msgType, iter);
                }
                it = mQueuedMessages.erase(it);
            }
        }

        void fillHeader(Header& header){
            header.set<FIX::Tag::BeginString>(beginString());
            header.set<FIX::Tag::BodyLength>("000");
            header.set<FIX::Tag::SenderCompID>(senderCompId());
            header.set<FIX::Tag::TargetCompID>(targetCompId());
        }

        void onDisconnected() override {
            close();
        }

        virtual void onMessage(const MsgChars& msgType, TokenIterator& fixIter) {}

        void onConnected() override
        {
            LOG_INFO("session senderCompId=({}) connected", senderCompId());
            state(SessionState::connected);
            // set header fields
            fillHeader(mHeader);
            sendLogon(false);
        }

        void stop(const std::string& reason) {
            sendLogout(reason);
        }

        void close() {
            state(SessionState::disconnected);
            stopHeartbeatTimer();
            mEventManagerInterface->stop();
        }

        void onMessage(const MsgChars& msgType, int msgSeqNo, const char* data, std::size_t length) override {

            TokenIterator fixIter(data, length);
            LOG_DEBUG("recv msg {}", msgType.data(), 2);

            onMessageRead(msgType, msgSeqNo, false, fixIter);
            onMessage(msgType, fixIter);
        }

        void startHeartbeatTimer()
        {   
            if (heartbeatInterval() == 0) {
                LOG_WARN("heartbeat interval is not set");
                stop("heartbeat interval is not set");
                return;
            }
            
            if (mIncommingMsgTimer || mOutgoingMsgTimer) {
                LOG_ERROR("heartbeat timers already started");
                stop("heartbeat timers already started");
                return;
            }

            LOG_INFO("starting in/out timers, HeartBtInt {}", heartbeatInterval());
            state(SessionState::logged_on);

            mIncommingMsgTimer = std::make_shared<RecurringTimer>(std::chrono::seconds(heartbeatInterval()), [this]() { this->sendTestRequest(); }, "msgseqin");
            mEventManagerInterface->addTimer(mIncommingMsgTimer);

            mOutgoingMsgTimer = std::make_shared<RecurringTimer>(std::chrono::seconds(heartbeatInterval()), [this]() { this->sendHeartbeat(); }, "msgseqout");
            mEventManagerInterface->addTimer(mOutgoingMsgTimer);
        }

        void stopHeartbeatTimer()
        {
            LOG_INFO("stop timers");
            mEventManagerInterface->removeTimer(mOutgoingMsgTimer);
            mOutgoingMsgTimer = nullptr; 
            mEventManagerInterface->removeTimer(mIncommingMsgTimer);
            mIncommingMsgTimer = nullptr;
        }

        void sendHeartbeat()
        {
            if (state() != SessionState::logged_on) {
                return;
            }
            LOG_INFO("heartbeat");

            Heartbeat heartbeat(&mHeader);
            send(heartbeat);
        }

        void removeResendTImer() {
            mEventManagerInterface->removeTimer(mResendTimer);
            mResendTimer.reset();
        }

        void onMessageRead(const MsgChars& msgType, int msgSeqNum, bool possDupFlag, TokenIterator& fixIter) {
            if (!validateFirstMessage(msgType)) {
                return;
            }

            if (msgType == FIX::MsgType::SequenceReset) {
                Header header;
                
                SequenceReset sequenceReset(&header);
                sequenceReset.deserialize(fixIter);
                processSequenceReset(sequenceReset, fixIter);
                return;
            }

            if (possDupFlag) {
                LOG_WARN("Ignoring PossDup Admin message with MsgType={}", msgType.data(), 2);
                return;
            }

            if (msgType == FIX::MsgType::Logon) {
                Header header;
                Logon logon(&header);
                logon.deserialize(fixIter);
                if(!processLogon(logon)) {
                    return;
                }
            }
            else {
                if (!validateSequenceNumbers(msgSeqNum, fixIter)) {
                    return;
                }
            }

            if (state() == SessionState::resending) {
                mQueuedMessages.emplace(std::make_pair(msgSeqNum, fixIter.getString()));
                mMissingSequences.erase(msgSeqNum);
                if (mMissingSequences.empty()) {
                    LOG_INFO("Resend complete");
                    flushBufferedMessages();                    
                    state(SessionState::logged_on);
                    removeResendTImer();
                }
            }

            incomingMsgSeqNum(msgSeqNum + 1);

            if (msgType == FIX::MsgType::Logout) {
                Header header;
                Logout logout(&header);
                logout.deserialize(fixIter);
                auto logout_text = logout. template get<FIX::Tag::Text>();
                processLogout(logout. template get<FIX::Tag::Text>());
            }
            else if (msgType == FIX::MsgType::Heartbeat) {
                Header header;
                Heartbeat heartbeat(&header);
                heartbeat.deserialize(fixIter);
                std::optional<std::string> testReqId;
                if (heartbeat. template isSet<FIX::Tag::TestReqID>()) {
                    testReqId = heartbeat. template get<FIX::Tag::TestReqID>();
                }
                processHeartbeat(testReqId);
            }
            else if (msgType == FIX::MsgType::TestRequest) {
                Header header;
                TestRequest testRequest(&header);
                testRequest.deserialize(fixIter);
                std::optional<std::string> testReqId;
                if (testRequest. template isSet<FIX::Tag::TestReqID>()) {
                    testReqId = testRequest. template get<FIX::Tag::TestReqID>();
                }
                processTestRequest(testReqId);
            }
            else if (msgType == FIX::MsgType::ResendRequest) {
                Header header;
                ResendRequest resendRequest(&header);
                resendRequest.deserialize(fixIter);
                if (!(resendRequest. template isSet<FIX::Tag::BeginSeqNo>() && resendRequest. template isSet<FIX::Tag::BeginSeqNo>())) {
                    LOG_ERROR("invalid resend reqest");
                    stop("invalid resend reqest ");
                    return;
                }
                auto beginSeqNo = resendRequest. template get<FIX::Tag::BeginSeqNo>();
                auto endSeqNo = resendRequest. template get<FIX::Tag::EndSeqNo>();
                processResendRequest(beginSeqNo, endSeqNo);
            }
            else if (msgType == FIX::MsgType::Reject) {
                Header header;
                Reject reject(&header);
                reject.deserialize(fixIter);
                LOG_ERROR("rejected recv: refTag {} reason{} text {}", reject. template get<FIX::Tag::RefTagID>(),
                                                        reject. template get<FIX::Tag::SessionRejectReason>(),
                                                        reject. template get<FIX::Tag::Text>());
                stop("rejected message detected");
            }

            mIncommingMsgTimer->reset();
        }

        bool validateSequenceNumbers(int msgSeqNum, TokenIterator& fixIter)
        {
            if (sequenceNumberIsHigh(msgSeqNum)) {
                mQueuedMessages.emplace(std::make_pair(msgSeqNum, fixIter.getString()));
                return false;
            }

            if (sequenceNumberIsLow(msgSeqNum)) {
                return false;
            }

            return true;
        }

        bool sequenceNumberIsHigh(int64_t msgSeqNum)
        {
            if (msgSeqNum > incomingMsgSeqNum()) {
                requestResend(msgSeqNum);
                return true;
            }
            
            return false;
        }

        bool sequenceNumberIsLow(int64_t msgSeqNum)
        {    
            if (msgSeqNum < incomingMsgSeqNum()) {
                const std::string text = "MsgSeqNum too low, expecting " + std::to_string(incomingMsgSeqNum()) + " but received " + std::to_string(msgSeqNum);
                LOG_ERROR(text);
                stop(text);
                return true;
            }

            return false;
        }

        void resendingTimerOut() {
            LOG_ERROR("could not recover using resend request, loging out!");
            stop("could not recover from gap");
        }

        void requestResend(uint32_t received_msg_seq_num)
        {
            LOG_INFO("Recoverable message sequence error, expected " + std::to_string(incomingMsgSeqNum()) + 
                        " received " + std::to_string(received_msg_seq_num) + " - initiating recovery");

            if (mState == SessionState::resending) {
                LOG_WARN("request resend needed while previous is pending");
            } else {
                mResendTimer = std::make_shared<Timer>([this]() { this->resendingTimerOut(); }, std::chrono::seconds(10), "resend_timer");
                mEventManagerInterface->addTimer(mResendTimer);
            }
            // collect missing sequence number
            for(auto seq = incomingMsgSeqNum(); seq < received_msg_seq_num; ++seq) {
                mMissingSequences.insert(seq);
            }

            state(SessionState::resending);

            mIncomingResentMsgSeqNum = incomingMsgSeqNum();
            mIncomingTargetMsgSeqNum = received_msg_seq_num - 1;

            LOG_INFO("Requesting resend, BeginSeqNo " + std::to_string(incomingMsgSeqNum()) + 
                        " EndSeqNo " + std::to_string(received_msg_seq_num));

            ResendRequest resendRequest(&mHeader);

            resendRequest. template set<FIX::Tag::BeginSeqNo>(mIncomingResentMsgSeqNum);
            resendRequest. template set<FIX::Tag::EndSeqNo>(mIncomingTargetMsgSeqNum);

            send(resendRequest);
        }

        bool validateFirstMessage(const MsgChars& msgType)
        {
            if (mLogonReceived) {
                return true;
            }

            if (msgType == FIX::MsgType::Logon) {
                return true;
            } 

            if (msgType == FIX::MsgType::Reject ||
                msgType == FIX::MsgType::Logout) {
                return true;
            }

            const std::string text = "First message is not a Logon";
            LOG_ERROR(text);
            stop(text);
            
            return false;
        }

        void sendLogon(bool reset_seq_num_flag)
        {
            auto sending_time = timestamp_string(qffixlib::timestamp_format::milliseconds);

            Logon msg(&mHeader);
            msg.mHeader-> template set<FIX::Tag::SendingTime>(sending_time);

            if (reset_seq_num_flag) {
                msg.mHeader-> template set<FIX::Tag::ResetSeqNumFlag>(reset_seq_num_flag);
            }

            msg. template set<FIX::Tag::EncryptMethod>(Values::EncryptMethod::None);
            msg. template set<FIX::Tag::HeartBtInt>(heartbeatInterval());
            msg. template set<FIX::Tag::ResetSeqNumFlag>(true);
            msg. template set<FIX::Tag::Username>(username());
            msg. template set<FIX::Tag::Password>(password());
            msg. template set<FIX::Tag::Text>(hmac_sha256_base64(password(), secretKey(), std::format("{}{}{}{}", sending_time , username() , targetCompId(), password())));
            msg. template set<FIX::Tag::DefaultApplVerID>(Values::DefaultApplVerID::FIX50SP2);

            send(msg, encode_options::standard_no_sending);
            state(SessionState::logging_on);

        }
        template<MsgChars MsgType, typename... Args>
        bool processLogon(FIXMessage<MsgType, Args...>& logon)
        {
            LOG_INFO("process logon");
            auto reset_seq_num_flag = logon. template get<FIX::Tag::ResetSeqNumFlag>();

            heartbeatInterval(logon. template get<FIX::Tag::HeartBtInt>());

            mLogonReceived = true;

            if (useNextExpectedMsgSeqNum())
            {
                LOG_INFO("logon with use next expected sequence number");
                if (!logon. template isSet<FIX::Tag::NextExpectedMsgSeqNum>()) {
                    const std::string text = "Logon does not contain NextExpectedMsgSeqNum";
                    LOG_ERROR(text);
                    stop(text);
                    return false;
                }

                auto next_expected = logon. template get<FIX::Tag::NextExpectedMsgSeqNum>();

                if (next_expected > outgoingMsgSeqNum()) {
                    const std::string text = "NextExpectedMsgSeqNum too high, expecting " + std::to_string(outgoingMsgSeqNum()) + " but received " + std::to_string(next_expected);
                    LOG_ERROR(text);
                    stop(text);
                    return false;
                }

                if (next_expected + 1 < outgoingMsgSeqNum()) {
                    const std::string text = "NextExpectedMsgSeqNum too low, expecting " + std::to_string(outgoingMsgSeqNum()) + " but received " + std::to_string(next_expected) + " - performing resend";
                    LOG_WARN(text);
                    state(SessionState::resending);
                    perform_resend(next_expected, outgoingMsgSeqNum());
                }

                startHeartbeatTimer();
                sendPostLogonTestRequest();
                return true;
            }

            auto msgSeqNum = logon.mHeader-> template get<FIX::Tag::MsgSeqNum>();
            if (reset_seq_num_flag) 
            {
                if (msgSeqNum != 1) {
                    LOG_ERROR("Invalid logon message, the ResetSeqNumFlag is set and the MsgSeqNum is not 1");
                    return false;
                }

                if (state() == SessionState::resetting) {
                    sendTestRequest();
                    return true;
                }

                LOG_INFO("Logon message received with ResetSeqNumFlag - resetting sequence numbers");

                startHeartbeatTimer();
                sendPostLogonTestRequest();
                return true;
            }

            if (sequenceNumberIsLow(msgSeqNum)) {
                return false;
            }

            if (sequenceNumberIsHigh(msgSeqNum)) {
                return false;
            }

            startHeartbeatTimer();
            sendPostLogonTestRequest();    
            return true;
        }


        void processLogout(const std::string& text)
        {
            LOG_INFO("Closing session in response to Logout {}", text);
            close();
        }

        void reset()
        {
            stopHeartbeatTimer();
            state(SessionState::resetting);
            outgoingMsgSeqNum(1);
            incomingMsgSeqNum(1);
        }

        void sendLogout(const std::string& text)
        {
            LOG_INFO("logging out with text {}", text);
            Logout logout(&mHeader);
            logout. template set<FIX::Tag::Text>(text);

            send(logout);
        }

        void sendPostLogonTestRequest()
        {
            if (testRequestDelay() != 0)
            {
                // TODO: allocate new timer
            }
            else 
            {
                LOG_INFO("send post logong test request");
                sendTestRequest();
            }
        }

        void sendTestRequest()
        {
            mExpectedTestRequestId = allocateTestRequestId();

            TestRequest testRequest(&mHeader);
            testRequest. template set<FIX::Tag::TestReqID>(std::to_string(*mExpectedTestRequestId) );

            send(testRequest);
        }

        uint32_t allocateTestRequestId()
        {
            return mNextTestRequestId++;
        }

        uint32_t allocateMsgSeqNumOut()
        {
            return mOutgoingMsgSeqNum++;
        }

        void processTestRequest(std::optional<std::string> testReqId)
        {  
            if (!testReqId) {
                const std::string text = "TestRequest does not contain a TestReqID"; 
                LOG_ERROR(text);
                return;
            } else {
                LOG_INFO("handle test request {}", *testReqId);
            }

            Heartbeat heartbeat(&mHeader);
            heartbeat. template set<FIX::Tag::TestReqID>(*testReqId);


            send(heartbeat);
        }

        void processHeartbeat(std::optional<std::string> testRequestId) {
            if (state() != SessionState::logging_on && 
                state() != SessionState::resetting && 
                state() != SessionState::resending) {
                return;
            }

            if (testRequestId) {
                if (!mExpectedTestRequestId) {
                    LOG_WARN("Received a Heartbeat with an unexpected TestReqID");
                    return;
                }

                if (*testRequestId != std::to_string(*mExpectedTestRequestId)) {
                    LOG_ERROR("Received a Heartbeat with an incorrect TestReqID during Logon - disconnecting");
                    stop("Received a Heartbeat with an incorrect TestReqID ");
                    return;
                }
            }
        }

        template<MsgChars MsgType, typename... Args>
        void processSequenceReset(const FIXMessage<MsgType, Args...>& sequenceReset, TokenIterator& fixIter)
        {
            if (!sequenceReset. template isSet<FIX::Tag::NewSeqNo>()) {
                const std::string text = "SequenceReset does not contain a NewSeqNo field";
                LOG_ERROR(text);
                return;
            }

            auto NewSeqNo = sequenceReset. template get<FIX::Tag::NewSeqNo>();

            if (!sequenceReset. template isSet<FIX::Tag::GapFillFlag>()) {
                const std::string text = "SequenceReset does not contain a GapFillFlag field";
                LOG_ERROR(text);
                return;
            }

            const bool GapFill = sequenceReset. template get<FIX::Tag::GapFillFlag>();

            if (NewSeqNo <= incomingMsgSeqNum()) {
                const std::string text = "NewSeqNo is not greater than expected MsgSeqNum = " + std::to_string(incomingMsgSeqNum());
                LOG_ERROR(text);
                return;
            }

            if (GapFill) {
                        
                if (!validateSequenceNumbers(sequenceReset.mHeader-> template get<FIX::Tag::MsgSeqNum>(), fixIter)) {
                    return;
                }

                if ((useNextExpectedMsgSeqNum() && state() != SessionState::logging_on) || 
                    (!useNextExpectedMsgSeqNum() && state() != SessionState::resending)) 
                {
                    const std::string text = "SequenceReset GapFill is not valid while not performing a resend";
                    LOG_ERROR(text);
                    return;
                }

                LOG_INFO("SeqenceReset (GapFill) received, NewSeqNo = " + std::to_string(NewSeqNo));
                
                mIncomingResentMsgSeqNum = NewSeqNo;
                incomingMsgSeqNum(NewSeqNo);
            }
            else {
                mIncomingResentMsgSeqNum = NewSeqNo;
                LOG_INFO("SeqenceReset (Reset) received, NewSeqNo = " + std::to_string(NewSeqNo));
            }

            if (state() == SessionState::resending && mIncomingResentMsgSeqNum >= mIncomingTargetMsgSeqNum) {                
                LOG_INFO("Resend gap filled");
                mMissingSequences.clear();
                mQueuedMessages.clear();
                state(SessionState::logged_on);
                removeResendTImer();
                sendTestRequest();
            }
        }

        void processResendRequest(int beginSeqNo, int endSeqNo)
        {
            LOG_INFO("Performing resend from BeginSeqNo=({}) to EndSeqNo=({})", beginSeqNo, endSeqNo);

            perform_resend(beginSeqNo, endSeqNo);

            sendPostLogonTestRequest();
        }

        void sendGapFill(uint32_t msg_seq_num, uint32_t new_seq_no)
        {   
            SequenceReset sequenceReset(&mHeader);
            sequenceReset.mHeader-> template set<FIX::Tag::MsgSeqNum>(msg_seq_num);
            sequenceReset. template set<FIX::Tag::GapFillFlag>(true);
            sequenceReset. template set<FIX::Tag::PossDupFlag>(true);
            sequenceReset. template set<FIX::Tag::NewSeqNo>(new_seq_no);

            send(sequenceReset, encode_options::standard & ~encode_options::set_msg_seq_num);
        }

        void perform_resend(uint32_t begin_msg_seq_num, uint32_t /*end_msg_seq_num*/)
        {
            sendGapFill(begin_msg_seq_num, outgoingMsgSeqNum());
        }


        SessionState state() const
        {
            return mState;
        }
        
        void state(SessionState state)
        {
            if (mState != state) {
                auto previous = mState;
                mState = state;
                LOG_INFO("change state from " + to_string(previous) + " to " + to_string(mState));
            }
        }

        void ensure_options_are_mutable() const
        {
            if (state() != SessionState::disconnected) {
                throw std::logic_error("session configuration cannot be changed while state = " + to_string(state()));
            }
        }


        const std::string& beginString() const noexcept
        {
            return mOptions.begin_string();
        }

        void beginString(const std::string& begin_string)
        {
            ensure_options_are_mutable();
            mOptions.begin_string(begin_string);
        }    

        const std::string& senderCompId() const noexcept
        {
            return mOptions.sender_comp_id();
        }

        void sender_comp_id(const std::string& sender_comp_id)
        {
            ensure_options_are_mutable();
            mOptions.sender_comp_id(sender_comp_id);
        }    

        const std::string& targetCompId() const noexcept
        {
            return mOptions.target_comp_id();
        }

        void targetCompId(const std::string& target_comp_id)
        {
            ensure_options_are_mutable();
            mOptions.target_comp_id(target_comp_id);
        }

        const std::string& username() const noexcept
        {
            return mOptions.username();
        }

        void username(const std::string& username)
        {
            ensure_options_are_mutable();
            mOptions.username(username);
        }

        const std::string& password() const noexcept
        {
            return mOptions.password();
        }

        void password(const std::string& password)
        {
            ensure_options_are_mutable();
            mOptions.password(password);
        }

        const std::string& secretKey() const noexcept
        {
            return mOptions.secretKey();
        }

        void secretKey(const std::string& secretKey)
        {
            ensure_options_are_mutable();
            mOptions.secretKey(secretKey);
        }

        uint32_t heartbeatInterval() const noexcept 
        { 
            return mOptions.heartbeat_interval(); 
        }

        void heartbeatInterval(uint32_t interval) noexcept 
        {
            // TODO - validate and start/stop defib if required
            mOptions.heartbeat_interval(interval); 
        }

        uint32_t testRequestDelay() const noexcept
        {
            return mOptions.test_request_delay();
        }

        void testRequestDelay(uint32_t delay)
        {
            ensure_options_are_mutable();
            mOptions.test_request_delay(delay);
        }

        qffixlib::timestamp_format timestampFormat() const noexcept
        {
            return mOptions.timestamp_format();
        }

        void timestampFormat(qffixlib::timestamp_format format) noexcept
        {
            mOptions.timestamp_format(format);
        }

        uint32_t incomingMsgSeqNum() const noexcept
        {
            return mIncomingMsgSeqNum;
        }

        void incomingMsgSeqNum(uint32_t msg_seq_num) noexcept
        {
            mIncomingMsgSeqNum = msg_seq_num;
        }

        uint32_t outgoingMsgSeqNum() const noexcept
        {
            return mOutgoingMsgSeqNum;
        }

        void outgoingMsgSeqNum(uint32_t msg_seq_num) noexcept
        {
            mOutgoingMsgSeqNum = msg_seq_num;
        }

        bool useNextExpectedMsgSeqNum() const noexcept
        {
            return mOptions.use_next_expected_msg_seq_num();
        }

        void useNextExpectedMsgSeqNum(bool value) noexcept
        {
            mOptions.use_next_expected_msg_seq_num(value);
        }

        template<MsgChars MsgType, typename... Args>
        void send(FIXMessage<MsgType, Args...>& message, int options = encode_options::standard) {
            if (message.MsgType == FIX::MsgType::Logon && message.mHeader-> template get<FIX::Tag::ResetSeqNumFlag>()) {
                state(SessionState::resetting);
                outgoingMsgSeqNum(1);
                incomingMsgSeqNum(1);
            }
            
            if ((options & encode_options::set_msg_seq_num) != 0) {
                message.mHeader-> template set<FIX::Tag::MsgSeqNum>(allocateMsgSeqNumOut());
            }

            if ((options & encode_options::set_sending_time) != 0) {
                message.mHeader-> template set<FIX::Tag::SendingTime>(timestamp_string(timestampFormat()));
            }

            message.serialize(mToSend);
            
            mWriter->sendMessage(mToSend.begin(), mToSend.length()); 

            mToSend.reset();

            if (mOutgoingMsgTimer) {
                mOutgoingMsgTimer->reset();
            }
        }

    private:

        SendingBuffer mToSend;
        Header mHeader;

        session_options mOptions;
        SessionState mState {SessionState::disconnected};
        bool mLogonReceived {false};

        std::optional<uint32_t> mExpectedTestRequestId {};
        uint32_t mNextTestRequestId {0};
        
        uint32_t mIncomingMsgSeqNum {1};
        uint32_t mOutgoingMsgSeqNum {1};

        uint32_t mIncomingResentMsgSeqNum {0};
        uint32_t mIncomingTargetMsgSeqNum {0};

        std::shared_ptr<Timer> mResendTimer {nullptr};

        std::shared_ptr<RecurringTimer> mIncommingMsgTimer {nullptr};
        std::shared_ptr<RecurringTimer> mOutgoingMsgTimer {nullptr};

        std::shared_ptr<Writer> mWriter {nullptr};
        std::shared_ptr<EventManagerInterface> mEventManagerInterface {nullptr};

        std::set<int64_t> mMissingSequences;
        std::map<int64_t, std::string> mQueuedMessages;
    };
}

#endif
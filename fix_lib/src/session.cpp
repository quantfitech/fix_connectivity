#include "session.hpp"
#include <functional>
#include <stdexcept>
#include "tag.hpp"
#include "logger.hpp"
#include "base64_hmac.h"
#include "logger.hpp"

#include "v50sp2/messages.hpp"

namespace qffixlib
{

    Session::Session(std::shared_ptr<SessionInterface> sess_interface, std::shared_ptr<EventManagerInterface> event_manager)
    : mSessionInterface(sess_interface),
      mEventManagerInterface(event_manager) {}

    void Session::set_writer(Writer* writer)
    {
        mWriter = writer;
    }

    void Session::fillHeader(Header& header){
        header.set<FIX::Tag::BeginString>("FIXT.1.1");
        header.set<FIX::Tag::BodyLength>("000");
        header.set<FIX::Tag::SenderCompID>(senderCompId());
        header.set<FIX::Tag::TargetCompID>(targetCompId());
    }


    void Session::onConnected()
    {
        LOG_INFO("session senderCompId=({}) connected", senderCompId());
        state(SessionState::connected);
        // set header
        mHeader.set<FIX::Tag::BeginString>("FIXT.1.1");
        mHeader.set<FIX::Tag::BodyLength>("000");
        mHeader.set<FIX::Tag::SenderCompID>(senderCompId());
        mHeader.set<FIX::Tag::TargetCompID>(targetCompId());
        logon();
    }

    void Session::close()
    {
        state(SessionState::disconnected);
    }

    void Session::onMessage(char msgType, int msgSeqNo, const char* data, std::size_t length) {

        TokenIterator fixIter(data, length);
        LOG_DEBUG("recv msg {}", msgType);

        onMessageRead(msgType, msgSeqNo, false, fixIter);

        mSessionInterface->onMessage(msgType, fixIter);
    }

    void Session::startHeartbeatTimer()
    {   
        if (heartbeatInterval() == 0) {
            LOG_WARN("heartbeat interval is not set");
            sendLogout("");
            return;
        }
        
        if (mIncommingMsgTimer || mOutgoingMsgTimer) {
            LOG_ERROR("heartbeat timers already started");
            sendLogout("");
            return;
        }

        LOG_INFO("starting in/out timers, HeartBtInt {}", heartbeatInterval());
        state(SessionState::logged_on);

        mIncommingMsgTimer = std::make_shared<RecurringTimer>(std::chrono::seconds(heartbeatInterval()), [this]() { this->sendTestRequest(); }, "msgseqin");
        mEventManagerInterface->addTimer(mIncommingMsgTimer);

        mOutgoingMsgTimer = std::make_shared<RecurringTimer>(std::chrono::seconds(heartbeatInterval()), [this]() { this->sendHeartbeat(); }, "msgseqout");
        mEventManagerInterface->addTimer(mOutgoingMsgTimer);
    }

    void Session::stopHeartbeatTimer()
    {
        mEventManagerInterface->removeTimer(mOutgoingMsgTimer);
        mOutgoingMsgTimer = nullptr; 
        mEventManagerInterface->removeTimer(mIncommingMsgTimer);
        mIncommingMsgTimer = nullptr;
    }

    void Session::sendHeartbeat()
    {
        if (state() != SessionState::logged_on) {
            return;
        }

        v50sp2::Message::Heartbeat heartbeat(&mHeader);
    
        send(heartbeat);
    }

    void Session::onMessageRead(char msgType, int msgSeqNum, bool possDupFlag, TokenIterator& fixIter) {
        if (!validateFirstMessage(msgType)) {
            return;
        }

        if (msgType == FIX::MsgType::SequenceReset) {
            Header header;
            v50sp2::Message::SequenceReset sequenceReset(&header);
            sequenceReset.deserialize(fixIter);
            processSequenceReset(sequenceReset);
            return;
        }

        if (possDupFlag) {
            LOG_WARN("Ignoring PossDup Admin message with MsgType={}", msgType);
            return;
        }

        if (msgType == FIX::MsgType::Logon) {
            Header header;
            v50sp2::Message::Logon logon(&header);
            logon.deserialize(fixIter);
            if(!processLogon(logon)) {
                return;
            }
        }
        else {
            if (!validateSequenceNumbers(msgSeqNum)) {
                return;
            }
        }

        incomingMsgSeqNum(msgSeqNum + 1);

        switch(msgType)
        {
            case FIX::MsgType::Logout:
            {
                Header header;
                v50sp2::Message::Logout logout(&header);
                logout.deserialize(fixIter);
                auto logout_text = logout.get<FIX::Tag::Text>();
                processLogout(logout.get<FIX::Tag::Text>());
                break;
            }
            case FIX::MsgType::Heartbeat:
            {
                Header header;
                v50sp2::Message::Heartbeat heartbeat(&header);
                heartbeat.deserialize(fixIter);
                std::optional<std::string> testReqId;
                if (heartbeat.isSet<FIX::Tag::TestReqID>()) {
                    testReqId = heartbeat.get<FIX::Tag::TestReqID>();
                }
                processHeartbeat(testReqId);
                break;
            }
            case FIX::MsgType::TestRequest:
            {
                Header header;
                v50sp2::Message::TestRequest testRequest(&header);
                testRequest.deserialize(fixIter);
                std::optional<std::string> testReqId;
                if (testRequest.isSet<FIX::Tag::TestReqID>()) {
                    testReqId = testRequest.get<FIX::Tag::TestReqID>();
                }
                processTestRequest(testReqId);
                break;
            }
            case FIX::MsgType::ResendRequest:
            {
                Header header;
                v50sp2::Message::ResendRequest resendRequest(&header);
                resendRequest.deserialize(fixIter);
                if (!(resendRequest.isSet<FIX::Tag::BeginSeqNo>() && resendRequest.isSet<FIX::Tag::BeginSeqNo>())) {
                    LOG_ERROR("invalid resend reqest");
                    close();
                    return;
                }
                auto beginSeqNo = resendRequest.get<FIX::Tag::BeginSeqNo>();
                auto endSeqNo = resendRequest.get<FIX::Tag::EndSeqNo>();
                processResendRequest(beginSeqNo, endSeqNo);
                break;
            }
            default:
                break;
        }

        mIncommingMsgTimer->reset( );
    }

    bool Session::validateSequenceNumbers(int msgSeqNum)
    {
        if (sequenceNumberIsHigh(msgSeqNum)) {
            return false;
        }

        if (sequenceNumberIsLow(msgSeqNum)) {
            return false;
        }

        return true;
    }

    bool Session::sequenceNumberIsHigh(int64_t msgSeqNum)
    {
        if (msgSeqNum > incoming_msg_seq_num()) {
            request_resend(msgSeqNum);
            return true;
        }
        
        return false;
    }

    bool Session::sequenceNumberIsLow(int64_t msgSeqNum)
    {    
        if (msgSeqNum < incoming_msg_seq_num()) {
            const std::string text = "MsgSeqNum too low, expecting " + std::to_string(incoming_msg_seq_num()) + " but received " + std::to_string(msgSeqNum);
            LOG_ERROR(text);
            sendLogout(text);
            return true;
        }

        return false;
    }

    void Session::request_resend(uint32_t received_msg_seq_num)
    {
        LOG_INFO("Recoverable message sequence error, expected " + std::to_string(incoming_msg_seq_num()) + 
                    " received " + std::to_string(received_msg_seq_num) + " - initiating recovery");

        state(SessionState::resending);

        m_incoming_resent_msg_seq_num = incoming_msg_seq_num();
        m_incoming_target_msg_seq_num = received_msg_seq_num;

        LOG_INFO("Requesting resend, BeginSeqNo " + std::to_string(incoming_msg_seq_num()) + 
                    " EndSeqNo " + std::to_string(received_msg_seq_num));



        v50sp2::Message::ResendRequest resendRequest(&mHeader);

        resendRequest.set<FIX::Tag::BeginSeqNo>(incoming_msg_seq_num());
        resendRequest.set<FIX::Tag::EndSeqNo>(received_msg_seq_num);

        send(resendRequest);
    }

    bool Session::validateFirstMessage(char msgType)
    {
        if (m_logon_received) {
            return true;
        }

        if (msgType == FIX::MsgType::Logon) {
            return true;
        } 

        if (msgType == FIX::MsgType::Reject ||
            msgType == FIX::MsgType::Logout)
        {
            return true;
        }

        const std::string text = "First message is not a Logon";
        LOG_ERROR(text);
        sendLogout(text);
        
        return false;
    }

    void Session::logon()
    {
        sendLogon();
    }

    void Session::sendLogon(bool reset_seq_num_flag)
    {
        auto sending_time = timestamp_string(qffixlib::timestamp_format::milliseconds);

        v50sp2::Message::Logon msg(&mHeader);
        msg.mHeader->set<FIX::Tag::SendingTime>(sending_time);

        if (reset_seq_num_flag) {
            msg.mHeader->set<FIX::Tag::ResetSeqNumFlag>(reset_seq_num_flag);
        }

        msg.set<FIX::Tag::EncryptMethod>('0');
        msg.set<FIX::Tag::HeartBtInt>(heartbeatInterval());
        msg.set<FIX::Tag::ResetSeqNumFlag>(true);
        msg.set<FIX::Tag::Username>(username());
        msg.set<FIX::Tag::Password>(password());
        msg.set<FIX::Tag::Text>(hmac_sha256_base64(password(), secretKey(), std::format("{}{}{}{}", sending_time , username() , targetCompId(), password())));
        msg.set<FIX::Tag::DefaultApplVerID>('9');

        send(msg, encode_options::standard_no_sending);
        state(SessionState::logging_on);

    }
    template<char MsgType, typename... Args>
    bool Session::processLogon(FIXMessage<MsgType, Args...>& logon)
    {
        LOG_INFO("process logon");
        auto reset_seq_num_flag = logon. template get<FIX::Tag::ResetSeqNumFlag>();

        heartbeatInterval(logon. template get<FIX::Tag::HeartBtInt>());

        m_logon_received = true;

        if (useNextExpectedMsgSeqNum())
        {
            LOG_INFO("logon with use next expected sequence number");
            if (!logon. template isSet<FIX::Tag::NextExpectedMsgSeqNum>()) {
                const std::string text = "Logon does not contain NextExpectedMsgSeqNum";
                LOG_ERROR(text);
                sendLogout(text);
                return false;
            }

            auto next_expected = logon. template get<FIX::Tag::NextExpectedMsgSeqNum>();

            if (next_expected > outgoingMsgSeqNum()) {
                const std::string text = "NextExpectedMsgSeqNum too high, expecting " + std::to_string(outgoingMsgSeqNum()) + " but received " + std::to_string(next_expected);
                LOG_ERROR(text);
                sendLogout(text);
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


    void Session::processLogout(const std::string& /*logout*/)
    {
        LOG_INFO("Closing session in response to Logout");
        close();
    }

    void Session::reset()
    {
        stopHeartbeatTimer();
        state(SessionState::resetting);
        outgoingMsgSeqNum(1);
        incomingMsgSeqNum(1);
    }

    void Session::sendLogout(const std::string& text)
    {
        v50sp2::Message::Logout logout(&mHeader);
        logout.set<FIX::Tag::Text>(text);

        send(logout);

        if (state() == SessionState::logged_on) {
            stopHeartbeatTimer();
        }

        close();
    }

    void Session::stop_test_request_timer()
    {

    }

    void Session::sendPostLogonTestRequest()
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

    void Session::sendTestRequest()
    {
        m_expected_test_request_id = allocateTestRequestId();

        v50sp2::Message::TestRequest testRequest(&mHeader);
        testRequest.set<FIX::Tag::TestReqID>( std::to_string(*m_expected_test_request_id) );

        send(testRequest);
    }

    uint32_t Session::allocateTestRequestId()
    {
        return m_next_test_request_id++;
    }

    uint32_t Session::allocateMsgSeqNumOut()
    {
        return m_outgoing_msg_seq_num++;
    }

    void Session::processTestRequest(std::optional<std::string> testReqId)
    {  
        if (!testReqId) {
            const std::string text = "TestRequest does not contain a TestReqID"; 
            LOG_ERROR(text);
            return;
        } else {
            LOG_INFO("handle test request {}", *testReqId);
        }

        v50sp2::Message::Heartbeat heartbeat(&mHeader);
        heartbeat.set<FIX::Tag::TestReqID>(*testReqId);


        send(heartbeat);
    }

    void Session::processHeartbeat(std::optional<std::string> testRequestId) {
        if (state() != SessionState::logging_on && 
            state() != SessionState::resetting && 
            state() != SessionState::resending) 
        {
            return;
        }

        if (testRequestId) 
        {
            if (!m_expected_test_request_id) {
                LOG_WARN("Received a Heartbeat with an unexpected TestReqID");
                return;
            }

            if (*testRequestId != std::to_string(*m_expected_test_request_id)) {
                LOG_ERROR("Received a Heartbeat with an incorrect TestReqID during Logon - disconnecting");
                close();
                return;
            }
        }
    }

    template<char MsgType, typename... Args>
    void Session::processSequenceReset(const FIXMessage<MsgType, Args...>& sequenceReset)
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


        if (NewSeqNo <= incoming_msg_seq_num()) {
            const std::string text = "NewSeqNo is not greater than expected MsgSeqNum = " + std::to_string(incoming_msg_seq_num());
            LOG_ERROR(text);
            return;
        }

        if (GapFill) {
                    
            if (!validateSequenceNumbers(sequenceReset.mHeader-> template get<FIX::Tag::MsgSeqNum>())) {
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
            
            m_incoming_resent_msg_seq_num = NewSeqNo;
            incomingMsgSeqNum(NewSeqNo);
        }
        else {
            m_incoming_resent_msg_seq_num = NewSeqNo;
            LOG_INFO("SeqenceReset (Reset) received, NewSeqNo = " + std::to_string(NewSeqNo));
        }

        if (state() == SessionState::resending && m_incoming_resent_msg_seq_num >= m_incoming_target_msg_seq_num) {
            LOG_INFO("Resend complete");
            sendTestRequest();
            //startHeartbeatTimer();
        }
    }



    void Session::processResendRequest(int beginSeqNo, int endSeqNo)
    {
        stop_test_request_timer();

        LOG_INFO("Performing resend from BeginSeqNo=({}) to EndSeqNo=({})", beginSeqNo, endSeqNo);

        perform_resend(beginSeqNo, endSeqNo);

        sendPostLogonTestRequest();
    }

    void Session::sendGapFill(uint32_t msg_seq_num, uint32_t new_seq_no)
    {   
        v50sp2::Message::SequenceReset sequenceReset(&mHeader);
        sequenceReset.mHeader->set<FIX::Tag::MsgSeqNum>(msg_seq_num);
        sequenceReset.set<FIX::Tag::GapFillFlag>(true);
        sequenceReset.set<FIX::Tag::PossDupFlag>(true);
        sequenceReset.set<FIX::Tag::NewSeqNo>(new_seq_no);

        send(sequenceReset, encode_options::standard & ~encode_options::set_msg_seq_num);
    }

    void Session::perform_resend(uint32_t begin_msg_seq_num, uint32_t /*end_msg_seq_num*/)
    {
        sendGapFill(begin_msg_seq_num, outgoingMsgSeqNum());
    }


    SessionState Session::state() const
    {
        return m_state;
    }
    
    void Session::state(SessionState state)
    {
        if (m_state != state) {
            auto previous = m_state;
            m_state = state;
            LOG_INFO("change state from " + to_string(previous) + " to " + to_string(m_state));
        }
    }

    void Session::ensure_options_are_mutable() const
    {
        if (state() != SessionState::disconnected) {
            throw std::logic_error("session configuration cannot be changed while state = " + to_string(state()));
        }
    }


    const std::string& Session::beginString() const noexcept
    {
        return m_options.begin_string();
    }

    void Session::beginString(const std::string& begin_string)
    {
        ensure_options_are_mutable();
        m_options.begin_string(begin_string);
    }    

    const std::string& Session::senderCompId() const noexcept
    {
        return m_options.sender_comp_id();
    }

    void Session::sender_comp_id(const std::string& sender_comp_id)
    {
        ensure_options_are_mutable();
        m_options.sender_comp_id(sender_comp_id);
    }    

    const std::string& Session::targetCompId() const noexcept
    {
        return m_options.target_comp_id();
    }

    void Session::targetCompId(const std::string& target_comp_id)
    {
        ensure_options_are_mutable();
        m_options.target_comp_id(target_comp_id);
    }

    const std::string& Session::username() const noexcept
    {
        return m_options.username();
    }

    void Session::username(const std::string& username)
    {
        ensure_options_are_mutable();
        m_options.username(username);
    }

    const std::string& Session::password() const noexcept
    {
        return m_options.password();
    }

    void Session::password(const std::string& password)
    {
        ensure_options_are_mutable();
        m_options.password(password);
    }

    const std::string& Session::secretKey() const noexcept
    {
        return m_options.secretKey();
    }

    void Session::secretKey(const std::string& secretKey)
    {
        ensure_options_are_mutable();
        m_options.secretKey(secretKey);
    }

    uint32_t Session::heartbeatInterval() const noexcept 
    { 
            return m_options.heartbeat_interval(); 
    }

    void Session::heartbeatInterval(uint32_t interval) noexcept 
    {
        // TODO - validate and start/stop defib if required
        m_options.heartbeat_interval(interval); 
    }

    uint32_t Session::testRequestDelay() const noexcept
    {
        return m_options.test_request_delay();
    }

    void Session::testRequestDelay(uint32_t delay)
    {
        ensure_options_are_mutable();
        m_options.test_request_delay(delay);
    }

    qffixlib::timestamp_format Session::timestampFormat() const noexcept
    {
        return m_options.timestamp_format();
    }

    void Session::timestampFormat(qffixlib::timestamp_format format) noexcept
    {
        m_options.timestamp_format(format);
    }

    uint32_t Session::incoming_msg_seq_num() const noexcept
    {
        return m_incoming_msg_seq_num;
    }

    void Session::incomingMsgSeqNum(uint32_t msg_seq_num) noexcept
    {
        m_incoming_msg_seq_num = msg_seq_num;
    }

    uint32_t Session::outgoingMsgSeqNum() const noexcept
    {
        return m_outgoing_msg_seq_num;
    }

    void Session::outgoingMsgSeqNum(uint32_t msg_seq_num) noexcept
    {
        m_outgoing_msg_seq_num = msg_seq_num;
    }

    bool Session::useNextExpectedMsgSeqNum() const noexcept
    {
        return m_options.use_next_expected_msg_seq_num();
    }

    void Session::useNextExpectedMsgSeqNum(bool value) noexcept
    {
        m_options.use_next_expected_msg_seq_num(value);
    }

}
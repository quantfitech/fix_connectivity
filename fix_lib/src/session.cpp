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
  mEventManagerInterface(event_manager){}

void Session::set_writer(Writer* writer)
{
    mWriter = writer;
}

void Session::fillHeader(Header& header){
    header.set<FIX::Tag::BeginString>("FIXT.1.1");
    header.set<FIX::Tag::BodyLength>("000");
    header.set<FIX::Tag::SenderCompID>(sender_comp_id());
    header.set<FIX::Tag::TargetCompID>(target_comp_id());
}


void Session::onConnected()
{
    LOG_INFO("session senderCompId=({}) connected", sender_comp_id());
    state(SessionState::connected);
    // set header
    mHeader.set<FIX::Tag::BeginString>("FIXT.1.1");
    mHeader.set<FIX::Tag::BodyLength>("000");
    mHeader.set<FIX::Tag::SenderCompID>(sender_comp_id());
    mHeader.set<FIX::Tag::TargetCompID>(target_comp_id());
    logon();
}

void Session::close()
{
    state(SessionState::disconnected);
}

void Session::onMessage(char msgType, int msgSeqNo, const char* data, std::size_t length) {

    /*auto end = data + length;
    auto begin = data;

    auto find_raw = [begin, end](const std::string& tag_str){
        auto it = std::search(begin, end, tag_str.begin(), tag_str.end());
        if (it == end) { std::make_pair(nullptr, nullptr); }
            
        auto it_end = std::find(it + tag_str.length(), end, SOH);  // Find end of tag value
        if (it_end == end) { std::make_pair(nullptr, nullptr);} 

        return std::make_pair(it + tag_str.length(), it_end); 
    };

    auto msg_res = find_raw("35=");
    if (msg_res.first == msg_res.second) {
        return;
    }
    char msgType = *(msg_res.second -1);

    auto res = find_raw("34=");
    if (res.first == res.second) {
        return;
    }
    int seqNo = std::stoi(std::string(res.first, res.second));

    auto it = msg_res.first - 3;
    */
  
    //TokenIterator fixIter(it, length - (it - begin) + 1);
    TokenIterator fixIter(data, length);
    LOG_DEBUG("recv msg {}", msgType);

    onMessageRead(msgType, msgSeqNo, false, fixIter);

    /*switch(msgType)
    {
        case FIX::MsgType::Logon:
        {
            Header header;
            v50sp2::Message::Logon logon(&header);
            logon.deserialize(fixIter);
            if(!processLogon(logon)) {
                return;
            }
            break;
        }
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
    }*/

    //fixlib::Message message;
    //message.decode(data, length);
    //onMessageRead(message);
    mSessionInterface->onMessage(msgType, fixIter);
}

void Session::startHeartbeatTimer()
{   
    if (heartbeat_interval() == 0) {
        LOG_WARN("heartbeat interval is not set");
        sendLogout("");
        return;
    }
    
    if (mIncommingMsgTimer || mOutgoingMsgTimer) {
        LOG_ERROR("heartbeat timers already started");
        sendLogout("");
        return;
    }

    LOG_INFO("starting in/out timers, HeartBtInt {}", heartbeat_interval());
    state(SessionState::logged_on);

    mIncommingMsgTimer = std::make_shared<RecurringTimer>(std::chrono::seconds(heartbeat_interval()), [this]() { this->sendTestRequest(); }, "msgseqin");
    mEventManagerInterface->addTimer(mIncommingMsgTimer);

    mOutgoingMsgTimer = std::make_shared<RecurringTimer>(std::chrono::seconds(heartbeat_interval()), [this]() { this->sendHeartbeat(); }, "msgseqout");
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

    auto heartbeat = Message(true, {
        Field(FIX::Tag::MsgType, FIX::MsgType::Heartbeat)
    });

    send(heartbeat);
}

void Session::onMessageRead(char msgType, int msgSeqNum, bool possDupFlag, TokenIterator& fixIter) {
    if (!validateFirstMessage(msgType)) {
        return;
    }

    //bool possDupFlag = false ;
    //if (message. template isSet<FIX::Tag::PossDupFlag>()) {
    //    possDupFlag = message. template get<FIX::Tag::PossDupFlag>();
    //}

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

    incoming_msg_seq_num(msgSeqNum + 1);

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


void Session::onMessageRead(qffixlib::Message& message)
{

    if (!validateChecksum(message)) {
        return;
    }

    if (!validateBodyLength(message)) {
        return;
    }

    if (!validateBeginString(message)) {
        return;
    }

    if (!validateCompIds(message)) {
        return;
    }

    if (!validateFirstMessage(message.MsgType())) {
        return;
    }

    const bool PossDupFlag = message.PossDupFlag();

    if (message.MsgType() == FIX::MsgType::SequenceReset) {
        process_sequence_reset(message, PossDupFlag);
        return;
    }

    if (PossDupFlag) {
        LOG_WARN("Ignoring PossDup Admin message with MsgType={}", message.MsgType());
        return;
    }

    if (message.MsgType() == FIX::MsgType::Logon) {
        if (!process_logon(message)) {
            return;
        }
    }
    else {
        if (!validateSequenceNumbers(message.MsgSeqNum())) {
            return;
        }
    }

    incoming_msg_seq_num(message.MsgSeqNum() + 1);

    if (message.MsgType() == FIX::MsgType::Heartbeat) {
        process_heartbeat(message);
    }
    else if (message.MsgType() == FIX::MsgType::TestRequest) {
        //process_test_request(message);
    }
    else if (message.MsgType() == FIX::MsgType::ResendRequest) {
        //process_resend_request(message);
    }
    else if (message.MsgType() == FIX::MsgType::Logout) {
        process_logout(message);
    } else {
        LOG_INFO("onMessageRead {}", message.MsgType() );
    }

    mIncommingMsgTimer->reset( );
}

bool Session::validateChecksum(const qffixlib::Message& message)
{
    auto CheckSum = message.fields().try_get(FIX::Tag::CheckSum);

    if (!CheckSum) 
    {
        const std::string text = "Received message without a CheckSum"; 
        LOG_ERROR(text);
        close();
        return false;
    }

    auto calculated_checksum = Message::formatChecksum(message.calculate_Checksum());

    if (CheckSum->value() != calculated_checksum) 
    {
        const std::string text = "Received message with an invalid CheckSum, expected " + calculated_checksum + " received "  + CheckSum->value();
        LOG_ERROR(text);
        close();
        return false;
    }

    return true;
}

bool Session::validateBodyLength(const qffixlib::Message& message)
{
    auto BodyLength = message.fields().try_get(FIX::Tag::BodyLength);

    if (!BodyLength) 
    {
        const std::string text = "Received message without a BodyLength";
        LOG_ERROR(text);
        return false;
    }

    auto calculated_body_length = message.calculateBodyLength();

    if (BodyLength->value() != std::to_string(calculated_body_length)) 
    {
        const std::string text = "Received message with an invalid BodyLength, expected " + std::to_string(calculated_body_length) + " received " + BodyLength->value(); 
        LOG_ERROR(text);
        close();
        return false;
    }

    return true;
}

bool Session::validateBeginString(const qffixlib::Message& message)
{
    auto BeginString = message.fields().try_get(FIX::Tag::BeginString);
    
    if (!BeginString) 
    {
        const std::string text = "Received message without a BeginString"; 
        LOG_ERROR(text);
        close();
        return false;
    }

    if (BeginString->value() != begin_string()) 
    {
        const std::string text = "Invalid BeginString, received " + BeginString->value() + " when expecting " + begin_string(); 
        LOG_ERROR(text);
        close();
        return false;
    }

    return true;
}

bool Session::validateCompIds(const qffixlib::Message& message)
{
    auto TargetCompId = message.fields().try_get(FIX::Tag::TargetCompID);

    if (!TargetCompId || TargetCompId->value() != sender_comp_id())
    {
        const std::string text = "Received TargetCompID '" + (TargetCompId ? TargetCompId->value() : "") + "' when expecting '" + sender_comp_id() + "'";
        LOG_ERROR(text);
        close();
        return false;
    }

    auto SenderCompId = message.fields().try_get(FIX::Tag::SenderCompID);

    if (!SenderCompId || SenderCompId->value() != target_comp_id()) 
    {
        const std::string text = "Received SenderCompID '" + (SenderCompId ? SenderCompId->value() : "") + "' when expecting '" + target_comp_id() + "'";
        LOG_ERROR(text);
        close();
        return false;
    }

    return true;
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
    /*auto resend_request = fixlib::Message(true, {
        Field( FIX::Tag::MsgType, FIX::MsgType::ResendRequest ),
        Field( FIX::Tag::BeginSeqNo, incoming_msg_seq_num() ),
        Field( FIX::Tag::EndSeqNo, received_msg_seq_num )
    });*/
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
    msg.set<FIX::Tag::HeartBtInt>(heartbeat_interval());
    msg.set<FIX::Tag::ResetSeqNumFlag>(true);
    msg.set<FIX::Tag::Username>(username());
    msg.set<FIX::Tag::Password>(password());
    msg.set<FIX::Tag::Text>(hmac_sha256_base64(password(), secretKey(), std::format("{}{}{}{}", sending_time , username() , target_comp_id(), password())));
    msg.set<FIX::Tag::DefaultApplVerID>('9');

    send(msg, encode_options::standard_no_sending);
    state(SessionState::logging_on);

    /*
    auto logon = Message(true, {
        Field( FIX::Tag::MsgType, "A" ),
        Field( FIX::Tag::EncryptMethod, "0"),
        Field( FIX::Tag::HeartBtInt, heartbeat_interval() ),
        Field( FIX::Tag::ResetSeqNumFlag, "Y"),
        Field( FIX::Tag::Username, username()),
        Field( FIX::Tag::Password, password()),
        Field( FIX::Tag::Text, hmac_sha256_base64(password(), std::format("{}{}{}{}", sending_time , username() , target_comp_id(), password()))),
        Field( FIX::Tag::DefaultApplVerID, "9" )
    });

    if (reset_seq_num_flag) {
        logon.fields().set(FIX::Tag::ResetSeqNumFlag, reset_seq_num_flag, set_operation::replace_first_or_append);
    }

    if (use_next_expected_msg_seq_num()) {
        logon.fields().set(FIX::Tag::NextExpectedMsgSeqNum, incoming_msg_seq_num(), set_operation::replace_first_or_append);
    }

    logon.fields().set(FIX::Tag::SendingTime, sending_time);

    send(logon, encode_options::standard_no_sending);
    

    state(SessionState::logging_on);
    */
}
template<char MsgType, typename... Args>
bool Session::processLogon(FIXMessage<MsgType, Args...>& logon)
{
    LOG_INFO("process logon");
    auto reset_seq_num_flag = logon. template get<FIX::Tag::ResetSeqNumFlag>();

     heartbeat_interval(logon. template get<FIX::Tag::HeartBtInt>());

    m_logon_received = true;

    if (use_next_expected_msg_seq_num())
    {
        LOG_INFO("logon with use next expected sequence number");
        if (!logon. template isSet<FIX::Tag::NextExpectedMsgSeqNum>()) {
            const std::string text = "Logon does not contain NextExpectedMsgSeqNum";
            LOG_ERROR(text);
            sendLogout(text);
            return false;
        }

        auto next_expected = logon. template get<FIX::Tag::NextExpectedMsgSeqNum>();

        if (next_expected > outgoing_msg_seq_num()) {
            const std::string text = "NextExpectedMsgSeqNum too high, expecting " + std::to_string(outgoing_msg_seq_num()) + " but received " + std::to_string(next_expected);
            LOG_ERROR(text);
            sendLogout(text);
            return false;
        }

        if (next_expected + 1 < outgoing_msg_seq_num()) {
            const std::string text = "NextExpectedMsgSeqNum too low, expecting " + std::to_string(outgoing_msg_seq_num()) + " but received " + std::to_string(next_expected) + " - performing resend";
            LOG_WARN(text);
            state(SessionState::resending);
            perform_resend(next_expected, outgoing_msg_seq_num());
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


bool Session::process_logon(const qffixlib::Message& logon)
{
    LOG_INFO("process logon");
    auto reset_seq_num_flag = logon.ResetSeqNumFlag();

    if (!extract_heartbeat_interval(logon)) {
        return false;
    }

    m_logon_received = true;

    if (use_next_expected_msg_seq_num())
    {
        LOG_INFO("logon with use next expected sequence number");
        auto NextExpectedMsgSeqNum = logon.fields().try_get(FIX::Tag::NextExpectedMsgSeqNum);

        if (!NextExpectedMsgSeqNum) {
            const std::string text = "Logon does not contain NextExpectedMsgSeqNum";
            LOG_ERROR(text);
            sendLogout(text);
            return false;
        }

        uint32_t next_expected = 0;

        try {
            next_expected = std::stoi(NextExpectedMsgSeqNum->value());
        }
        catch (std::exception& ex) {
            const std::string text = NextExpectedMsgSeqNum->value() + " is not a valid value for NextExpectedMsgSeqNum";
            LOG_ERROR(text);
            sendLogout(text);
            return false;
        }

        if (next_expected > outgoing_msg_seq_num()) {
            const std::string text = "NextExpectedMsgSeqNum too high, expecting " + std::to_string(outgoing_msg_seq_num()) + " but received " + std::to_string(next_expected);
            LOG_ERROR(text);
            sendLogout(text);
            return false;
        }

        if (next_expected + 1 < outgoing_msg_seq_num()) {
            const std::string text = "NextExpectedMsgSeqNum too low, expecting " + std::to_string(outgoing_msg_seq_num()) + " but received " + std::to_string(next_expected) + " - performing resend";
            LOG_WARN(text);
            state(SessionState::resending);
            perform_resend(next_expected, outgoing_msg_seq_num());
        }

        startHeartbeatTimer();
        sendPostLogonTestRequest();
        return true;
    }

    if (reset_seq_num_flag) 
    {
        if (logon.MsgSeqNum() != 1) {
            LOG_ERROR("Invalid logon message, the ResetSeqNumFlag is set and the MsgSeqNum is not 1");
            return false;
        }

        if (state() == SessionState::resetting) {
            sendTestRequest();
            return true;
        }

        LOG_INFO("Logon message received with ResetSeqNumFlag - resetting sequence numbers");
        //reset();
        //send_logon(true);
        //send_post_logon_test_request();
        startHeartbeatTimer();
        sendPostLogonTestRequest();
        return true;
    }

    if (sequenceNumberIsLow(logon.MsgSeqNum())) {
        return false;
    }

    if (sequenceNumberIsHigh(logon.MsgSeqNum())) {
        return false;
    }

    startHeartbeatTimer();
    sendPostLogonTestRequest();    
    return true;
}

void Session::process_logout(const qffixlib::Message& /*logout*/)
{
    LOG_INFO("Closing session in response to Logout");
    close();
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
    outgoing_msg_seq_num(1);
    incoming_msg_seq_num(1);
}

bool Session::extract_heartbeat_interval(const qffixlib::Message& logon)
{
    auto heartBtInt = logon.fields().try_get(FIX::Tag::HeartBtInt);

    if (!heartBtInt) 
    {
        const std::string text = "Logon message does not contain a HeartBtInt"; 
        LOG_ERROR(text);
        sendLogout(text);
        return false;
    }

    try
    {
        heartbeat_interval(std::stoi(heartBtInt->value()));
    }
    catch (std::exception& ex)
    {
        const std::string text = heartBtInt->value() + " is not a valid numeric HeartBtInt";
        LOG_ERROR(text);
        sendLogout(text);
        return false;
    }

    return true;
}

void Session::sendLogout(const std::string& text)
{
    /*auto logout = Message(true, { 
        Field( FIX::Tag::MsgType, FIX::MsgType::Logout),
        Field( FIX::Tag::Text, text )
    });*/
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
    if (test_request_delay() != 0)
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

    //auto test_request = Message(true, {
    //    Field( FIX::Tag::MsgType, FIX::MsgType::TestRequest ),
    //    Field( FIX::Tag::TestReqID, *m_expected_test_request_id )
    //});
    v50sp2::Message::TestRequest testRequest(&mHeader);
    testRequest.set<FIX::Tag::TestReqID>( std::to_string(*m_expected_test_request_id) );

    send(testRequest);
}

uint32_t Session::allocateTestRequestId()
{
    return m_next_test_request_id++;
}

uint32_t Session::allocate_outgoing_msg_seq_num()
{
    return m_outgoing_msg_seq_num++;
}

void Session::processTestRequest(std::optional<std::string> testReqId)
{
   //auto testReqId = test_request.fields().try_get(FIX::Tag::TestReqID);    

    if (!testReqId) {
        const std::string text = "TestRequest does not contain a TestReqID"; 
        LOG_ERROR(text);
        return;
    } else {
        LOG_INFO("handle test request {}", *testReqId);
    }

    /*auto heartbeat = Message(true, {
        Field( FIX::Tag::MsgType, FIX::MsgType::Heartbeat ),
        Field( FIX::Tag::TestReqID, testReqId->value() )
    });*/

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

    //auto testReqId = heartbeat.fields().try_get(FIX::Tag::TestReqID);

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

void Session::process_heartbeat(const Message& heartbeat)
{
    if (state() != SessionState::logging_on && 
        state() != SessionState::resetting && 
        state() != SessionState::resending) 
    {
        return;
    }

    auto testReqId = heartbeat.fields().try_get(FIX::Tag::TestReqID);

    if (testReqId) 
    {
        if (!m_expected_test_request_id) {
            LOG_WARN("Received a Heartbeat with an unexpected TestReqID");
            return;
        }

        if (testReqId->value() != std::to_string(*m_expected_test_request_id)) {
            LOG_ERROR("Received a Heartbeat with an incorrect TestReqID during Logon - disconnecting");
            close();
            return;
        }
    }

    //state(SessionState::logged_on);
    //startHeartbeatTimer();
}

void Session::process_sequence_reset(const qffixlib::Message& sequence_reset, bool /*poss_dup*/)
{
    auto NewSeqNo_field = sequence_reset.fields().try_get(FIX::Tag::NewSeqNo);

    if (!NewSeqNo_field) {
        const std::string text = "SequenceReset does not contain a NewSeqNo field";
        LOG_ERROR(text);
        return;
    }

    const bool GapFill = sequence_reset.GapFillFlag();

    uint32_t NewSeqNo = 0;

    try {
        NewSeqNo = std::stoi(NewSeqNo_field->value());
    }
    catch (std::exception& ex) {
        const std::string text = NewSeqNo_field->value() + " is not a valid value for NewSeqNo";
        LOG_ERROR(text);
        return;
    }

    if (NewSeqNo <= incoming_msg_seq_num()) {
        const std::string text = "NewSeqNo is not greater than expected MsgSeqNum = " + std::to_string(incoming_msg_seq_num());
        LOG_ERROR(text);
        return;
    }

    if (GapFill) {
                
        if (!validateSequenceNumbers(sequence_reset.MsgSeqNum())) {
            return;
        }

        if ((use_next_expected_msg_seq_num() && state() != SessionState::logging_on) || 
            (!use_next_expected_msg_seq_num() && state() != SessionState::resending)) 
        {
            const std::string text = "SequenceReset GapFill is not valid while not performing a resend";
            LOG_ERROR(text);
            return;
        }

        LOG_INFO("SeqenceReset (GapFill) received, NewSeqNo = " + std::to_string(NewSeqNo));
        
        m_incoming_resent_msg_seq_num = NewSeqNo;
        incoming_msg_seq_num(NewSeqNo);
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

        if ((use_next_expected_msg_seq_num() && state() != SessionState::logging_on) || 
            (!use_next_expected_msg_seq_num() && state() != SessionState::resending)) 
        {
            const std::string text = "SequenceReset GapFill is not valid while not performing a resend";
            LOG_ERROR(text);
            return;
        }

        LOG_INFO("SeqenceReset (GapFill) received, NewSeqNo = " + std::to_string(NewSeqNo));
        
        m_incoming_resent_msg_seq_num = NewSeqNo;
        incoming_msg_seq_num(NewSeqNo);
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

    /*auto BeginSeqNo = resend_request.fields().try_get(FIX::Tag::BeginSeqNo);

    if (!BeginSeqNo) {
        const std::string text = "ResendRequest does not contain a BeginSeqNo field";
        //LOG_ERROR(text);
        return;
    }

    auto EndSeqNo = resend_request.fields().try_get(FIX::Tag::EndSeqNo);

    if (!EndSeqNo) {
        const std::string text = "ResendRequest does not contain a EndSeqNo field";
        //LOG_ERROR(text);
        return;
    }

    const uint32_t begin = std::stoi(BeginSeqNo->value());
    uint32_t end = std::stoi(EndSeqNo->value());
    */
    LOG_INFO("Performing resend from BeginSeqNo=({}) to EndSeqNo=({})", beginSeqNo, endSeqNo);

    perform_resend(beginSeqNo, endSeqNo);

    sendPostLogonTestRequest();
}

void Session::sendGapFill(uint32_t msg_seq_num, uint32_t new_seq_no)
{
    /*auto sequence_reset = Message(true, {
        Field( FIX::Tag::MsgType, FIX::MsgType::SequenceReset ),
        Field( FIX::Tag::MsgSeqNum, msg_seq_num ),
        Field( FIX::Tag::GapFillFlag, true ),
        Field( FIX::Tag::PossDupFlag, true ),
        Field( FIX::Tag::NewSeqNo, new_seq_no )
    });*/
    
    v50sp2::Message::SequenceReset sequenceReset(&mHeader);
    sequenceReset.mHeader->set<FIX::Tag::MsgSeqNum>(msg_seq_num);
    sequenceReset.set<FIX::Tag::GapFillFlag>(true);
    sequenceReset.set<FIX::Tag::PossDupFlag>(true);
    sequenceReset.set<FIX::Tag::NewSeqNo>(new_seq_no);

    send(sequenceReset, encode_options::standard & ~encode_options::set_msg_seq_num);
}

void Session::perform_resend(uint32_t begin_msg_seq_num, uint32_t /*end_msg_seq_num*/)
{
    sendGapFill(begin_msg_seq_num, outgoing_msg_seq_num());
}

void Session::send(Message& message, int options)
{
    if (message.MsgType() == FIX::MsgType::Logon && message.ResetSeqNumFlag())
    {
        state(SessionState::resetting);
        outgoing_msg_seq_num(1);
        incoming_msg_seq_num(1);
    }

    if ((options & encode_options::set_begin_string) != 0) {
        message.fields().set(FIX::Tag::BeginString, begin_string());
    }

    message.fields().set(FIX::Tag::SenderCompID, sender_comp_id());
    message.fields().set(FIX::Tag::TargetCompID, target_comp_id());
    
    if ((options & encode_options::set_msg_seq_num) != 0) {
        message.fields().set(FIX::Tag::MsgSeqNum, allocate_outgoing_msg_seq_num());
    }

    if ((options & encode_options::set_sending_time) != 0) {
        message.fields().set(FIX::Tag::SendingTime, timestamp_string(timestamp_format()));
    }

    if ((options & encode_options::set_checksum) != 0) {
        // message::encode will give this a real value
        message.fields().set(FIX::Tag::CheckSum, "", set_operation::replace_first_or_append);    
    }

    auto encoded_size = message.encode(mSendingBuffer, options);
    mWriter->sendMessage(mSendingBuffer, encoded_size); 
    std::memset(mSendingBuffer, 0, SENDING_BUFFER_SIZE);

    if (mOutgoingMsgTimer) {
        mOutgoingMsgTimer->reset();
    }
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
        //state_changed(previous, m_state);
    }
}

void Session::ensure_options_are_mutable() const
{
    if (state() != SessionState::disconnected) {
        throw std::logic_error("session configuration cannot be changed while state = " + to_string(state()));
    }
}


const std::string& Session::begin_string() const noexcept
{
    return m_options.begin_string();
}

void Session::begin_string(const std::string& begin_string)
{
    ensure_options_are_mutable();
    m_options.begin_string(begin_string);
}    

const std::string& Session::sender_comp_id() const noexcept
{
    return m_options.sender_comp_id();
}

void Session::sender_comp_id(const std::string& sender_comp_id)
{
    ensure_options_are_mutable();
    m_options.sender_comp_id(sender_comp_id);
}    

const std::string& Session::target_comp_id() const noexcept
{
    return m_options.target_comp_id();
}

void Session::target_comp_id(const std::string& target_comp_id)
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

uint32_t Session::heartbeat_interval() const noexcept 
{ 
        return m_options.heartbeat_interval(); 
}

void Session::heartbeat_interval(uint32_t interval) noexcept 
{
    // TODO - validate and start/stop defib if required
    m_options.heartbeat_interval(interval); 
}

uint32_t Session::test_request_delay() const noexcept
{
    return m_options.test_request_delay();
}

void Session::test_request_delay(uint32_t delay)
{
    ensure_options_are_mutable();
    m_options.test_request_delay(delay);
}

qffixlib::timestamp_format Session::timestamp_format() const noexcept
{
    return m_options.timestamp_format();
}

void Session::timestamp_format(qffixlib::timestamp_format format) noexcept
{
    m_options.timestamp_format(format);
}

uint32_t Session::incoming_msg_seq_num() const noexcept
{
    return m_incoming_msg_seq_num;
}

void Session::incoming_msg_seq_num(uint32_t msg_seq_num) noexcept
{
    m_incoming_msg_seq_num = msg_seq_num;
}

uint32_t Session::outgoing_msg_seq_num() const noexcept
{
    return m_outgoing_msg_seq_num;
}

void Session::outgoing_msg_seq_num(uint32_t msg_seq_num) noexcept
{
    m_outgoing_msg_seq_num = msg_seq_num;
}

bool Session::use_next_expected_msg_seq_num() const noexcept
{
    return m_options.use_next_expected_msg_seq_num();
}

void Session::use_next_expected_msg_seq_num(bool value) noexcept
{
    m_options.use_next_expected_msg_seq_num(value);
}

}
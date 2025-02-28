#ifndef SESSION_HPP
#define SESSION_HPP

#include "session_options.hpp"
#include "session_state.hpp"
#include "writer.hpp"
#include "timer.hpp"
#include "connection_interface.hpp"
#include "session_interface.hpp"
#include "event_manager_interface.hpp"
#include "utils.hpp"
#include "fix_message.hpp"
#include "tag.hpp"
#include "session_options.hpp"

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

    class Session : public ConnectionInterface
    {
    public:

        Session(std::shared_ptr<SessionInterface>, std::shared_ptr<EventManagerInterface>);

        void set_writer(Writer* writer);

        //void open();
        void close();

        SessionState state() const;

        void onConnected() override;

        void onDisconnected() override {}

        void onMessage(char, int, const char*, std::size_t) override;

        bool isConnected() override { return false; }

        template<char MsgType, typename... Args>
        void send(FIXMessage<MsgType, Args...>& message, int options = encode_options::standard);

        //void send(message& message, int options, const std::string& sending_time);

        const std::string& beginString() const noexcept;
        void beginString(const std::string& begin_string);    

        const std::string& senderCompId() const noexcept;
        void sender_comp_id(const std::string& sender_comp_id);    

        const std::string& targetCompId() const noexcept;
        void targetCompId(const std::string& target_comp_id);

        const std::string& username() const noexcept;
        void username(const std::string& username);

        const std::string& password() const noexcept;
        void password(const std::string& username);

        const std::string& secretKey() const noexcept;
        void secretKey(const std::string& secretKey);
    
        uint32_t heartbeatInterval() const noexcept;
        void heartbeatInterval(uint32_t interval) noexcept;

        uint32_t testRequestDelay() const noexcept;
        void testRequestDelay(uint32_t delay);

        qffixlib::timestamp_format timestampFormat() const noexcept;
        void timestampFormat(qffixlib::timestamp_format format) noexcept;

        uint32_t incoming_msg_seq_num() const noexcept;
        void incomingMsgSeqNum(uint32_t msg_seq_num) noexcept;

        uint32_t outgoingMsgSeqNum() const noexcept;
        void outgoingMsgSeqNum(uint32_t msg_seq_num) noexcept;

        bool useNextExpectedMsgSeqNum() const noexcept;
        void useNextExpectedMsgSeqNum(bool value) noexcept;

        //void on_message(const std::string&);
        void fillHeader(Header& header);

    private:

        void state(SessionState state);

        void ensure_options_are_mutable() const;

        void onMessageRead(char MsgType, int msgSeqNum, bool posDupFlag, TokenIterator& fixIt);

        void logon();
        
        template<char MsgType, typename... Args>
        bool processLogon(FIXMessage<MsgType, Args...>& message);

        void processLogout(const std::string&);

        void processTestRequest(std::optional<std::string>);

        void processHeartbeat(std::optional<std::string>);

        template<char MsgType, typename... Args>
        void processSequenceReset(const FIXMessage<MsgType, Args...>&);

        void processResendRequest(int, int);
        
        
        void sendLogon(bool reset_seq_num_flag = false);
        void sendLogout(const std::string& text);
        void sendPostLogonTestRequest();
        void sendTestRequest();
        void sendGapFill(uint32_t msg_seq_num, uint32_t new_seq_no);

        void perform_resend(uint32_t begin_msg_seq_num, uint32_t end_msg_seq_num);

        bool validateFirstMessage(char);
        bool validateSequenceNumbers(int msgSeqNum);

        bool sequenceNumberIsHigh(int64_t);
        bool sequenceNumberIsLow(int64_t);
        
        void request_resend(uint32_t received_msg_seq_num);
        void reset();

        uint32_t allocateTestRequestId();
        uint32_t allocateMsgSeqNumOut();

        void startHeartbeatTimer();
        void sendHeartbeat();
        void stopHeartbeatTimer();
        void stop_test_request_timer();

        SendingBuffer mToSend;
        Header mHeader;

        session_options m_options;
        SessionState m_state = SessionState::disconnected;
        bool m_logon_received = false;

        std::optional<uint32_t> m_expected_test_request_id;
        uint32_t m_next_test_request_id = 0;
        
        // TODO - these two need to go into a struct for persistence
        uint32_t m_incoming_msg_seq_num = 1;
        uint32_t m_outgoing_msg_seq_num = 1;

        uint32_t m_incoming_resent_msg_seq_num = 0;
        uint32_t m_incoming_target_msg_seq_num = 0;

        std::shared_ptr<RecurringTimer> mIncommingMsgTimer;
        std::shared_ptr<RecurringTimer> mOutgoingMsgTimer;

        Writer* mWriter = nullptr;
        std::shared_ptr<SessionInterface> mSessionInterface;
        std::shared_ptr<EventManagerInterface> mEventManagerInterface;
    };

    template<char MsgType, typename... Args>
    void Session::send(FIXMessage<MsgType, Args...>& message, int options) {
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

}

#endif
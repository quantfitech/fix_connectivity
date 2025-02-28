#ifndef SESSION_H
#define SESSION_H

#include <chrono>
#include <memory>
#include <ctime>
#include "connection.hpp"
//#include "clientconnection.h"
//#include "serverconnection.h"
//#include "boostclientconnection.h"
//#include "boostserverconnection.h"
#include "message.hpp"
#include "message_factory.hpp"
#include "constants.hpp"


enum class SequenceNumberState {
    IN_SYNC = 0,
    GAP = 1,
    RETRANSMISSION = 2,
};

class Session {
public:
	Session(bool is_server);
	~Session() = default;
	void start();
	void end();

    void onMessage(Message& msg);
    SequenceNumberState validateReceivedSequenceNumber(unsigned);

	void handle_logon(Message& msg);
	void handle_checksum(Message& msg);
	void handle_heart_beat(Message& msg);
	void handle_send_heart_beat_a(Message& msg);
	void handle_send_heart_beat_b(Message& msg);
	void handle_send_test_request();
	void handle_reject();
	void handle_resend_request();
	void handle_message_standard_header(Message& msg);
	void handle_sequence_reset_gap_fill(Message& msg);
	void handle_sequence_reset_reset(Message& msg);
	void handle_logout(const Message& msg);
	void receive_and_handle_message();
	bool is_session_running();

    void resetSequenceNumbers();

    void incrementSeqNoOut() { mSeqNumOut++; }
    void incrementSeqNoIn() { mSeqNumIn++; }

    bool isTargetTooHigh(unsigned msgSeqNum) { return msgSeqNum > mSeqNumIn; }
    bool isTargetTooLow(unsigned msgSeqNum) { return msgSeqNum < mSeqNumIn; }

    bool verify(const Message &msg);


private:
    bool mLogonSent = false;
    bool mLogonReceived = false;

	//bool is_user_duplicated_or_unauthenticated(Message& msg) const;
	std::unique_ptr<Connection> connection_;
	  unsigned int next_msg_seq_num_ = 0;
    unsigned mSeqNumOut;
    unsigned mSeqNumIn;

    std::string mSenderCompId;
    std::string mTargetCompId;

	bool mIsRunnnig = false;
	//bool is_server_;
	//static constexpr bool use_boost_ = constants::USE_BOOST;
	double mHeartbeatInterval = 1e9;
	//bool received_valid_message_;
	std::chrono::time_point<std::chrono::system_clock> mLastReceivedMessageTime = std::chrono::system_clock::now();
};

#endif
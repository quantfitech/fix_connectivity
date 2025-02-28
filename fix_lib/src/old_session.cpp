#include "session.hpp"
#include "client_connection.hpp"
#include "logger.hpp"
#include "tag.hpp"


Session::Session(bool) {
	//is_server_ = is_server;
	//if constexpr (use_boost_) {
	//	if (is_server_)
	//		connection_ = std::make_unique<BoostServerConnection>();
	//	else
	//		connection_ = std::make_unique<BoostClientConnection>();
	//}
	//else {
		//if (is_server_)
		//	connection_ = std::make_unique<ServerConnection>();
		//else
			connection_ = std::make_unique<ClientConnection>();
	//}
}

SequenceNumberState Session::validateReceivedSequenceNumber(unsigned seqNo){
    if (mSeqNumIn == seqNo) {
        return SequenceNumberState::IN_SYNC;
    } else if ( mSeqNumIn < seqNo) {
        //self.logger.warning(f'gap in sequence number (Received: {seq_no} Expected: {self.seqNumIn})')
        return SequenceNumberState::GAP;
    } else {
        //self.logger.warning(f'retransmission in sequence number (Received: {seq_no} Expected: {self.seqNumIn})')
        return SequenceNumberState::RETRANSMISSION;
    }
}

void Session::resetSequenceNumbers() {
    mSeqNumIn = 1;
    mSeqNumOut = 1;
}

bool Session::	verify(const Message &msg) {
  //const MsgType *pMsgType = 0;
  //const MsgSeqNum *pMsgSeqNum = 0;

  try {
    //const Header &header = msg.getHeader();
    unsigned msgSeqNum = msg.get_uint(FIX::Tag::MsgSeqNum);

    //pMsgType = FIELD_GET_PTR(header, MsgType);
    //const SenderCompID &senderCompID = FIELD_GET_REF(header, SenderCompID);
    //const TargetCompID &targetCompID = FIELD_GET_REF(header, TargetCompID);
    //const SendingTime &sendingTime = FIELD_GET_REF(header, SendingTime);

    //if (checkTooHigh || checkTooLow) {
    //  pMsgSeqNum = FIELD_GET_PTR(header, MsgSeqNum);
   // }

    //if (!validLogonState(*pMsgType)) {
    //  throw std::logic_error("Logon state is not valid for message");
    //}

    //if (!isGoodTime(sendingTime)) {
    //  doBadTime(msg);
    //  return false;
   // }
    //if (!isCorrectCompID(senderCompID, targetCompID)) {
    //  doBadCompID(msg);
    //  return false;
    //}

    if (isTargetTooHigh(msgSeqNum)) {
      //doTargetTooHigh(msg);
      return false;
    } else if (isTargetTooLow(msgSeqNum)) {
      //doTargetTooLow(msg); 
       //generateLogout();
      return false;
    }

    /*if ((checkTooHigh || checkTooLow) && m_state.resendRequested()) {
      SessionState::ResendRange range = m_state.resendRange();

      if (*pMsgSeqNum >= range.second) {
        m_state.onEvent(
            "ResendRequest for messages FROM: " + SEQNUM_CONVERTOR::convert(range.first)
            + " TO: " + SEQNUM_CONVERTOR::convert(range.second) + " has been satisfied.");
        m_state.resendRange(0, 0);
      }
    }*/
  } catch (std::exception &e) {
    //m_state.onEvent(e.what());
    end();
    return false;
  }

  mLastReceivedMessageTime = std::chrono::system_clock::now();
  //m_state.testRequest(0);

  //fromCallback(pMsgType ? *pMsgType : MsgType(), msg, m_sessionID);
  return true;
}


void Session::onMessage(Message& msg){
    MsgType msgType = msg.getMsgType();
    if (msgType == MsgType::LOGON) {
        handle_logon(msg);
    } else if (msgType == MsgType::HEARTBEAT) {
      //nextHeartbeat(message, now);
      verify(msg);
      incrementSeqNoIn();
    } else if (msgType == MsgType::TESTREQUEST) {
      verify(msg);
      //nextTestRequest(message, now);
      //send heartbeat
      //Message heartbeat(MsgType::HEARTBEAT);
      //sendRaw(heartbeat);
    } else if (msgType == MsgType::SEQUENCERESET) {
        handle_sequence_reset_reset(msg);
    } else if (msgType == MsgType::LOGOUT) {
      handle_logout(msg);
    } else if (msgType == MsgType::RESENDREQUEST) {
      handle_resend_request();
    } else if (msgType == MsgType::REJECT) {
      handle_reject();
    } else {
      if (!verify(msg)) {
        return;
      }
      incrementSeqNoIn();
    }
}

void Session::start() {
	connection_->open_connection();
	//is_session_running_ = true;
}

void Session::end() {
	connection_->close_connection();
	//is_session_running_ = false;
}

void Session::receive_and_handle_message() {
	Message msg = connection_->receive_message();
	if (msg.serialize().size() == 0) {
		std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - mLastReceivedMessageTime;
		if (elapsed_seconds > (std::chrono::duration<double>)(mHeartbeatInterval * 1.2)) {
			Logger().log_info(const_cast<char*>("No messages received for a while"));
			handle_send_test_request(); //Scenario 6
		}
		else if (elapsed_seconds > (std::chrono::duration<double>)mHeartbeatInterval) {
			Logger().log_info(const_cast<char*>("No messages received for a while"));
			handle_send_heart_beat_a(msg); //Scenario 4_a
		}
		return;
	}
	/*received_valid_message_ = true;
	last_received_message_time_ = std::chrono::system_clock::now();
	Logger().log_info(const_cast<char*>("Message received"));
	Logger().log_info(msg.serialize().c_str());
	if (!logon_message_received_) {
		handle_logon(msg); //Scenario 1B, 1S and 2S
		return;
	}
	if (msg.has_tag(constants::CHECKSUM)) {
		handle_checksum(msg); //Scenario 3
	}
	if (received_valid_message_)
		handle_message_standard_header(msg); //Scenario 2_a, 2_b, and 2_c
	if (received_valid_message_) {
		if (msg.get_tag_value(constants::MSG_TYPE) == constants::TEST_REQUEST) {
			handle_send_heart_beat_b(msg); //Scenario 4_b
			return;
		}
		if (msg.get_tag_value(constants::MSG_TYPE) == constants::HEART_BEAT) {
			handle_heart_beat(msg); //Scenario 5
			return;
		}
		if (msg.get_tag_value(constants::MSG_TYPE) == constants::REJECT) {
			handle_reject(); //Scenario 7
			return;
		}
		if (msg.get_tag_value(constants::MSG_TYPE) == constants::RESEND_REQUEST) {
			handle_resend_request(); //Scenario 8
			return;
		}
		if (msg.get_tag_value(constants::MSG_TYPE) == constants::LOGOUT) {
			handle_logout(); //Scenario 12 and 13
			return;
		}
		if (msg.get_tag_value(constants::MSG_TYPE) == constants::SEQUENCE_RESET_MSG_TYPE) {
			if (msg.get_tag_value(constants::GAP_FILL_FLAG) == FixedString("Y")) {
				handle_sequence_reset_gap_fill(msg); //Scenario 10
				return;
			}
		}
		if (msg.get_tag_value(constants::MSG_TYPE) == constants::SEQUENCE_RESET_MSG_TYPE) {
			if (msg.get_tag_value(constants::GAP_FILL_FLAG) == FixedString("N")) {
				handle_sequence_reset_reset(msg); //Scenario 11
				return;
			}
		}
		Logger().log_warning(const_cast<char *>("Ingoring message because it is invalid or garbled")); //Scenario 2_d
	}*/
}

void Session::handle_logon(Message& msg) {
      if (mLogonSent) {
           mLogonReceived = true;
           bool resetSeqNum = msg.get_bool(FIX::Tag::ResetSeqNumFlag);
           if (resetSeqNum){
                resetSequenceNumbers();
           }
           //unsigned msg_seq_num = msg.get<unsigned>(FIX::Tag::NextExpectedMsgSeqNum);
      } else {
           // log error
           end(); 
      }
	/*if (msg.get_tag_value(constants::MSG_TYPE) == constants::LOGON) {
		if (msg.get_tag_value(constants::MSG_SEQ_NUM).to_uint() > next_msg_seq_num_) {
			FixedString serialized_response = MessageFactory().create_resend_request(next_msg_seq_num_, next_msg_seq_num_).serialize();
			connection_->send_message(serialized_response);
			Logger().log_info(const_cast<char*>("Message sent"));
			Logger().log_info(serialized_response.c_str());
		}
		else {
			logon_message_received_ = true;
			next_msg_seq_num_ = msg.get_tag_value(constants::MSG_SEQ_NUM).to_int() + 1;
			FixedString serialized_response = MessageFactory().create_logon("usr", "pwd", "txt").serialize();
			connection_->send_message(serialized_response);
			Logger().log_info(const_cast<char*>("Message sent"));
			Logger().log_info(serialized_response.c_str());
		}
	} else if (is_server_ && is_user_duplicated_or_unauthenticated(msg)) {
		Logger().log_error(const_cast<char*>("duplicated/unauthenticated/non-configured identity"));
		end();
	} else {
		Logger().log_error(const_cast<char*>("invalid Logon message (the first message must be Logon)"));
		connection_->send_message(MessageFactory().create_logout().serialize());
		end();
	}*/
}

void Session::handle_checksum(Message& msg) {
	FixedString serialized_message = msg.serialize();
	bool msg_ended_by_soh = (serialized_message[(int)serialized_message.size() - 1] == constants::SOH[0]);
	if (!msg_ended_by_soh) {
		Logger().log_warning(const_cast<char*>("Garbled message"));
		//received_valid_message_ = false;
		return;
	}
	bool msg_checksum_value_has_length_3 = (msg.get_tag_value(constants::CHECKSUM).size() == 3);
	if (!msg_checksum_value_has_length_3) {
		Logger().log_warning(const_cast<char*>("Garbled message"));
		//received_valid_message_ = false;
		return;
	}
	/*bool msg_ended_by_checksum_tag =
		(serialized_message[(int)serialized_message.size() - 7] == '1') &&
		(serialized_message[(int)serialized_message.size() - 6] == '0');
	*/if (!msg_checksum_value_has_length_3) {
		Logger().log_warning(const_cast<char*>("Garbled message"));
		//received_valid_message_ = false;
		return;
	}
	bool msg_checksum_correct = (msg.get_checksum() == msg.get_tag_value(constants::CHECKSUM));
	if (!msg_checksum_correct) {
		Logger().log_warning(const_cast<char*>("Garbled message"));
		//eceived_valid_message_ = false;
		return;
	}
}

void Session::handle_heart_beat(Message& msg) {
	if (msg.has_tag(constants::HEART_BT_INT)) {
		//heartbeat_interval_ = std::stod(msg.get_tag_value(constants::HEART_BT_INT).c_str());
	}
	//next_msg_seq_num_++;
	//Accept message
}

void Session::handle_send_heart_beat_a(Message&) {
	FixedString serialized_response = MessageFactory().create_heartbeat({}).serialize();
	connection_->send_message(serialized_response);
	Logger().log_info(const_cast<char*>("Message sent"));
	Logger().log_info(serialized_response.c_str());
	//next_msg_seq_num_++;
	//Accept message
}

void Session::handle_send_heart_beat_b(Message& msg) {
	FixedString test_req_id = msg.get_tag_value(constants::TEST_REQ_ID);
	FixedString serialized_response = MessageFactory().create_heartbeat_with_test_req_id(test_req_id).serialize();
	connection_->send_message(serialized_response);
	Logger().log_info(const_cast<char*>("Message sent"));
	Logger().log_info(serialized_response.c_str());
	//next_msg_seq_num_++;
	//Accept message
}

void Session::handle_send_test_request() {
	FixedString serialized_response = MessageFactory().create_heartbeat_with_test_req_id(constants::TEST_REQ_ID_VALUE).serialize();
	connection_->send_message(serialized_response);
	Logger().log_info(const_cast<char*>("Message sent"));
	Logger().log_info(serialized_response.c_str());
	//next_msg_seq_num_++;
	//Accept message
}

void Session::handle_reject() {
	//next_msg_seq_num_++;
	//Accept message
}

void Session::handle_resend_request() {
	FixedString serialized_response = MessageFactory().create_resend_request(next_msg_seq_num_, next_msg_seq_num_).serialize();
	connection_->send_message(serialized_response);
	Logger().log_info(const_cast<char*>("Message sent"));
	Logger().log_info(serialized_response.c_str());
	//next_msg_seq_num_++;
	//Accept message
}

void Session::handle_message_standard_header(Message&) {
	/*unsigned int msg_seq_num = msg.get_tag_value(constants::MSG_SEQ_NUM).to_int();
	if (msg_seq_num == next_msg_seq_num_) {
		//Accept msg_seq_num
	}
	else if (msg_seq_num > next_msg_seq_num_) {
		FixedString serialized_response = MessageFactory().create_resend_request(next_msg_seq_num_, next_msg_seq_num_).serialize();
		connection_->send_message(serialized_response);
		Logger().log_info(const_cast<char*>("Message sent"));
		Logger().log_info(serialized_response.c_str());
		//received_valid_message_ = false;
	} else if (msg_seq_num < next_msg_seq_num_) {
		if (!(msg.get_tag_value(constants::POSS_DUP_FLAG) == FixedString("Y")))
			if (!(msg.get_tag_value(constants::MSG_TYPE) == constants::SEQUENCE_RESET_MSG_TYPE)) {
				FixedString serialized_response = MessageFactory().create_logout().serialize();
				connection_->send_message(serialized_response);
				Logger().log_info(const_cast<char*>("Message sent"));
				Logger().log_info(serialized_response.c_str());
				Logger().log_error(const_cast<char*>("MsgSeqNum too low"));
				end();
			}
	}*/
}

void Session::handle_sequence_reset_gap_fill(Message& msg) {
	if (msg.get_tag_value(constants::NEW_SEQ_NUM).to_int() > msg.get_tag_value(constants::MSG_SEQ_NUM).to_int()) {
		if (msg.get_tag_value(constants::NEW_SEQ_NUM).to_uint() > next_msg_seq_num_) {
			FixedString serialized_response = MessageFactory().create_resend_request(next_msg_seq_num_, msg.get_tag_value(constants::MSG_SEQ_NUM).to_int()).serialize();
			connection_->send_message(serialized_response);
			Logger().log_info(const_cast<char*>("Message sent"));
			Logger().log_info(serialized_response.c_str());
			return;
		}
	}
	else if (msg.get_tag_value(constants::NEW_SEQ_NUM).to_int() > msg.get_tag_value(constants::MSG_SEQ_NUM).to_int()) {
		if (msg.get_tag_value(constants::NEW_SEQ_NUM).to_uint() == next_msg_seq_num_) {
			next_msg_seq_num_ = msg.get_tag_value(constants::NEW_SEQ_NUM).to_int();
			return;
		}
	}
	else if (msg.get_tag_value(constants::NEW_SEQ_NUM).to_int() > msg.get_tag_value(constants::MSG_SEQ_NUM).to_int()) {
		if (msg.get_tag_value(constants::NEW_SEQ_NUM).to_uint() < next_msg_seq_num_) {
			if (msg.get_tag_value(constants::POSS_DUP_FLAG) == FixedString("Y")) {
				// ignore message
				return;
			}
		}
	}
	else if (msg.get_tag_value(constants::NEW_SEQ_NUM).to_int() > msg.get_tag_value(constants::MSG_SEQ_NUM).to_int()) {
		if (msg.get_tag_value(constants::NEW_SEQ_NUM).to_uint() < next_msg_seq_num_) {
			if (!(msg.get_tag_value(constants::POSS_DUP_FLAG) == FixedString("Y"))) {
				FixedString serialized_response = MessageFactory().create_logout().serialize();
				connection_->send_message(serialized_response);
				Logger().log_info(const_cast<char*>("Message sent"));
				Logger().log_info(serialized_response.c_str());
				Logger().log_error(const_cast<char*>("MsgSeqNum too low"));
				end();
				return;			
			}
		}
	}
	else if (msg.get_tag_value(constants::NEW_SEQ_NUM).to_int() <= msg.get_tag_value(constants::MSG_SEQ_NUM).to_int()) {
		if (msg.get_tag_value(constants::NEW_SEQ_NUM).to_uint() == next_msg_seq_num_) {
			FixedString serialized_response = MessageFactory().create_reject(next_msg_seq_num_,
																			 FixedString(constants::MSG_SEQ_NUM),
																			 FixedString("attempt to lower sequence number, invalid value NewSeqNo(36)")).serialize();
			connection_->send_message(serialized_response);
			Logger().log_info(const_cast<char*>("Message sent"));
			Logger().log_info(serialized_response.c_str());
			Logger().log_info(const_cast<char*>("MsgSeqNum too low"));
		}
	}
}

void Session::handle_sequence_reset_reset(Message&) {
	/*bool isGapFill = false;
	GapFillFlag gapFillFlag;
	
	if (sequenceReset.getFieldIfSet(gapFillFlag)) {
		isGapFill = gapFillFlag;
	}

	if (!verify(sequenceReset, isGapFill, isGapFill)) {
		return;
	}

	NewSeqNo newSeqNo;
	if (sequenceReset.getFieldIfSet(newSeqNo)) {
		if (newSeqNo > getExpectedTargetNum()) {
			m_state.setNextTargetMsgSeqNum(MsgSeqNum(newSeqNo));
		} else if (newSeqNo < getExpectedTargetNum()) {
			generateReject(sequenceReset, SessionRejectReason_VALUE_IS_INCORRECT);
		}
	}

	if (msg.get_tag_value(constants::NEW_SEQ_NUM).to_uint() > next_msg_seq_num_) {
		next_msg_seq_num_ = msg.get_tag_value(constants::NEW_SEQ_NUM).to_int();
	}
	else if (msg.get_tag_value(constants::NEW_SEQ_NUM).to_uint() == next_msg_seq_num_) {
		next_msg_seq_num_ = msg.get_tag_value(constants::NEW_SEQ_NUM).to_int();
		Logger().log_warning(const_cast<char*>("NewSeqNo(36) = NextNumIn"));
	}
	else if (msg.get_tag_value(constants::NEW_SEQ_NUM).to_uint() < next_msg_seq_num_) {
		Message response = MessageFactory().create_reject(next_msg_seq_num_,
														  FixedString(constants::MSG_SEQ_NUM),
														  FixedString(""));
		response.add_field(constants::SESSION_REJECT_REASON, "5");
		FixedString serialized_response = response.serialize();
		connection_->send_message(serialized_response);
		Logger().log_info(const_cast<char*>("Message sent"));
		Logger().log_info(serialized_response.c_str());
	}*/
}

void Session::handle_logout(const Message&) {
	end();
	//Accept message and end session
}

bool Session::is_session_running() {
	return mIsRunnnig;
}

//bool Session::is_user_duplicated_or_unauthenticated(Message&) const {
//	return false; // Assuming that we have only one user and one active connection
//}
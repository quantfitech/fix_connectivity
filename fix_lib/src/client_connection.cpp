#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include "client_connection.hpp"
#include "logger.hpp"
#include "fix_types.hpp"

namespace qffixlib {

	ClientConnection::ClientConnection(std::shared_ptr<ConnectionInterface> observer, 
									   std::unique_ptr<SocketInterface> socket,
									   std::shared_ptr<EventManager> eventManager): 
	mConnectionObserver(observer),
	mSocket(std::move(socket)),
	mEventManager(eventManager)
	{
		mBuffer.reserve(mBufferCapacity);
	}

	void ClientConnection::openConnection(const std::string& host, int port) {
		LOG_INFO("open connection {}:{}", host, port);

		mSocket->openConnection(host, port);
	}

	void ClientConnection::onConnected() {
		LOG_INFO("connected fd={}", getFd());
		mSocket->onConnected();
		mIsConnected = true;
		if (mConnectionObserver){
			mConnectionObserver->onConnected();
		}
	}

	void ClientConnection::sendMessage(const char* data, std::size_t length) {
		LOG_DEBUG("sending from fd={}", getFd());
		auto sentSize = mSocket->sendMessage(data, length);
		if (sentSize < static_cast<int>(length)) {
			LOG_INFO("sending buffer is full, making it writable")    
			mEventManager->makeReadableWritable(getFd());
    	}
	}

	bool ClientConnection::extractMessage() {
		if (mReadingBuffer.offset() < 12) {
			//no begin and length
			return false;
		}
		
		auto result = mReadingBuffer.tryGetTag("8=", mReadingBuffer.begin());
		if (result.first == result.second) {
			return false;
		}

		result = mReadingBuffer.tryGetTag("9=", result.second);
		if (result.first == result.second) {
			return false;
		}

		auto bodyLength = std::stoi(std::string(result.first, result.second));

		auto beginToBodyEnd = std::distance(mReadingBuffer.begin(), result.second) + 1;

		size_t messageLength = beginToBodyEnd + bodyLength + 7;
		if (mReadingBuffer.offset() < messageLength) return false;  // Not enough data

		LOG_DEBUG("body length: {} buffer {} msg length: {}", bodyLength, mReadingBuffer.offset(), messageLength);

		auto bodylengthEnd = result.second;

		result = mReadingBuffer.tryGetTag("35=", result.second);
		if (result.first == result.second) {
			throw std::runtime_error("msg type not found!");
		}
	
		MsgChars msgType;
		auto msgTypeLength = std::distance(result.first, result.second);
		if (msgTypeLength == 1) {
			msgType[0] = *(result.first);
			msgType[1] = '\n';
		} else if (msgTypeLength == 2) {
			msgType[0] = *(result.first);
			msgType[1] = *(result.first+1);
		} else {
			throw std::runtime_error("unexpected messagetype, length {}" + std::to_string(msgTypeLength));
		}

		result = mReadingBuffer.tryGetTag("34=", bodylengthEnd);
		if (result.first == result.second) {
			throw std::runtime_error("msg type not found!");
		}

		auto msgSeqNo = std::stoi(std::string(result.first, result.second));

		spdlog::level::level_enum current_level = spdlog::default_logger()->level();
		if (current_level == spdlog::level::debug) {
			std::string msgStr(mReadingBuffer.data(), messageLength);
			std::replace(msgStr.begin(), msgStr.end(), '\x01', '|');
			LOG_DEBUG("EXTRACT {}", msgStr);
		}

		mConnectionObserver->onMessage(msgType, msgSeqNo, mReadingBuffer.data() + beginToBodyEnd, messageLength - beginToBodyEnd);

		return mReadingBuffer.consume(messageLength);

	}

	int ClientConnection::onData() {
		LOG_DEBUG("on data fd={}", getFd());
		while(true) {			
			auto bytesReceived = mSocket->receiveMessage(mReadingBuffer.data(), mReadingBuffer.offset(), mReadingBuffer.remaining());
       		if (bytesReceived > 0) {
				mReadingBuffer.append(bytesReceived);
				while (extractMessage()) {
				}
			} else {
				 if (mSocket->getLastReadResult(bytesReceived) != RecvCode::ERROR) {
					// No more data available
					break;
				} 
				else {
					LOG_ERROR("Failed to read response from server");
					close();
					return 0;
				}
			}
		}
		return 1;
	}

	void ClientConnection::close() {
		if (mConnectionObserver) {
			mConnectionObserver->onDisconnected();
		}
		mSocket->closeConnection();
		mIsConnected = false;
	}

	void ClientConnection::onError() {
		LOG_ERROR("onError fd={}", getFd());
		close();
	}

	void ClientConnection::onClose() {
		LOG_ERROR("onClose fd={}", getFd());
		close();
	}

	int ClientConnection::onWrite() {
		return mSocket->onWrite();
	}
}
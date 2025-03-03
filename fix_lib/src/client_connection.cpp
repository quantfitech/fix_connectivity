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

	ClientConnection::ClientConnection(std::shared_ptr<ConnectionInterface> observer, SocketInterface * socket, std::shared_ptr<EventManager> eventManager): 
	mConnectionObserver(observer),
	mSocket(socket),
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

	void ClientConnection::disconnect() {
		LOG_INFO("close connection fd={}", getFd());
		mSocket->closeConnection();
	}

	void  ClientConnection::sendMessage(const char* data, std::size_t length) {
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

		LOG_DEBUG("EXTRACT {}", std::string(mReadingBuffer.begin(), mReadingBuffer.begin() + mReadingBuffer.offset()));
		
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

		char msgType = *(result.first);

		result = mReadingBuffer.tryGetTag("34=", bodylengthEnd);
		if (result.first == result.second) {
			throw std::runtime_error("msg type not found!");
		}

		auto msgSeqNo = std::stoi(std::string(result.first, result.second));

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
					mConnectionObserver->onDisconnected();
					mSocket->closeConnection();
					return 0;
				}
			}
		}
		return 1;
	}
	void ClientConnection::onError() {
		LOG_ERROR("onError fd={}", getFd());
		if (mConnectionObserver) {
			mConnectionObserver->onDisconnected();
		}
		mIsConnected = false;
	}

	void ClientConnection::onClose() {
		LOG_ERROR("onClose fd={}", getFd());
		if (mConnectionObserver) {
			mConnectionObserver->onDisconnected();
		}
		mIsConnected = false;
	}

	int ClientConnection::onWrite() {
		return mSocket->onWrite();
	}
}
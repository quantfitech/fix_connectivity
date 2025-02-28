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

	void ClientConnection::open_connection(const std::string& host, int port) {
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

		//if (mBuffer.data()[0] == FIELD_SEPARATOR) {
		//	return false;
		//}
		
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

		/*auto end = mBuffer.begin() + mBufferSize;
		LOG_DEBUG("EXTRACT {}", std::string( mBuffer.begin(), end));
		std::string begin = "8=";
		auto begin_it = std::search(mBuffer.begin(), end, begin.begin(), begin.end());
		if (begin_it == end) { return false; }

		std::string bodyLengthRaw = "9=";
		auto bodyLength_it = std::search(mBuffer.begin(), end, bodyLengthRaw.begin(), bodyLengthRaw.end());
		if (bodyLength_it == end) { return false; }
			
		auto length_end = std::find(bodyLength_it + 2, end, SOH);  // Find end of tag value
		if (length_end == end) { return false;} 

		auto bodyLength = std::stoi(std::string(bodyLength_it + 2 , length_end));
		if (bodyLength == -1) return false;  // Can't determine message length
		
		LOG_DEBUG("body length: {} buff {}", bodyLength, mBufferSize);

		// Approximate message length (header + body + checksum)
		size_t messageLength = std::distance(begin_it, length_end) + 1 + bodyLength + 7;
		if (mBufferSize < messageLength) return false;  // Not enough data

		LOG_DEBUG("msg length: {} buff {}", messageLength, mBufferSize);
		

		mConnectionObserver->onMessage(mBuffer.data(), messageLength);

		if (messageLength == mBufferSize) {
			mBufferSize = 0;
			return false;
		} else {
			std::move(mBuffer.begin() + messageLength, mBuffer.begin() + mBufferSize, mBuffer.begin());
			mBufferSize -= messageLength;
			return true;
		}*/
		return mReadingBuffer.consume(messageLength);

	}

	int ClientConnection::onData() {
		LOG_DEBUG("on data fd={}", getFd());
		while(true) {
			/*auto remaining = mBufferCapacity - mBufferSize;
			if (remaining < 0) {
				LOG_WARN("growing data buffer {} 2 times", mBufferCapacity);
				mBuffer.resize(mBufferCapacity * 2);
				mBufferCapacity *=2;
				remaining = mBufferCapacity - mBufferSize;
			}
			auto bytesReceived = mSocket->receiveMessage(mBuffer.data(), mBufferSize, remaining);
			*/
			auto bytesReceived = mSocket->receiveMessage(mReadingBuffer.data(), mReadingBuffer.offset(), mReadingBuffer.remaining());
       		if (bytesReceived > 0) {
          	    //LOG_DEBUG("received {} length {}", std::string(mBuffer.begin() + mBufferSize, mBuffer.begin() + mBufferSize + bytesReceived), bytesReceived);
				//mBufferSize += bytesReceived;
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
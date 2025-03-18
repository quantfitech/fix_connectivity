#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

//#include "connection.hpp"
#include "connection_interface.hpp"
#include "socket_interface.hpp"
#include "timer.hpp"
#include "reader_buffer.hpp"
#include "event_manager.hpp"
#include "file_descriptor.hpp"
#include "writer.hpp"

namespace qffixlib {

	using namespace qfapp;
	
	class ClientConnection : public FileDescriptor, public Writer {
	public:
		ClientConnection(std::shared_ptr<ConnectionInterface>, std::unique_ptr<SocketInterface>, std::shared_ptr<EventManager>);
		~ClientConnection() = default;
		void openConnection(const std::string& host, int port);		

		int onData() override;    // Called when data is available
        void onError() override;   // Called on errors
        void onClose() override;   // Called on any other event
		int onWrite() override;
		void onConnected() override;

		void close();

		bool extractMessage();
		void sendMessage(const char*, std::size_t) override;

		int getFd() const override { return mSocket->getFd(); }
		bool isInitiator() const override { return true; }
		bool isConnected() const override { return mIsConnected; };

		void provideData(const std::string& data) { 
			std::memcpy(mReadingBuffer.data(), data.data(), data.length());
			mReadingBuffer.append(data.length());
		}

	private:
		bool mIsConnected = false;

		std::size_t mBufferCapacity = 8192;
		std::vector<char> mBuffer; 
		std::size_t mBufferSize {0};

		ReaderBuffer mReadingBuffer;

		std::shared_ptr<ConnectionInterface> mConnectionObserver;
		std::unique_ptr<SocketInterface> mSocket{nullptr};
		std::shared_ptr<qfapp::Timer> mConnectionRetry;
		std::shared_ptr<qfapp::EventManager> mEventManager;
	};
}
#endif
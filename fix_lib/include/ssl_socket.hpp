#ifndef SSL_SOCKET_H
#define SSL_SOCKET_H

#include "writer.hpp"
#include "socket_interface.hpp"
#include <openssl/ssl.h>
#include <openssl/err.h>
#include "writer_buffer.hpp"

namespace qffixlib {

	#define MAX_OVERFLOW_BUFFER 8192

	class SSLSocket : public SocketInterface {
	public:
		SSLSocket() = default;
		virtual ~SSLSocket() = default;
		bool openConnection(const std::string& host, int port) override;
		void closeConnection() override;
        int onWrite() override;
		void onConnected() override;
		
        int receiveMessage(char*, std::size_t, std::size_t) override;
		int sendMessage(const char*, std::size_t) override;
        RecvCode getLastReadResult(std::size_t) override;

	private:
		
		//char mOverflowBuffer[MAX_OVERFLOW_BUFFER];
		//size_t mOverflowOffset{0};

		WriterBuffer mWriteBuffer;

		bool isConnecting{true};
        SSL_CTX* ctx = nullptr;
        SSL* ssl = nullptr;
	};
}
#endif //SSl_SOCKET_H
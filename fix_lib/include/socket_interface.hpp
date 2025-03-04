#ifndef SOCKET_INTERFACE_H
#define SOCKET_INTERFACE_H

#include <string>

namespace qffixlib {


    enum class RecvCode {
        NO_ERROR = 0,
        WOULD_BLOCK = 1,
        ERROR = 2,
    };

	class SocketInterface {
	public:
		virtual ~SocketInterface() = default;
		virtual bool openConnection(const std::string& host, int port) = 0;
		virtual void closeConnection() = 0;
        virtual int  onWrite() = 0;
        virtual void onConnected() = 0;
		
        virtual int receiveMessage(char*, std::size_t, std::size_t) = 0;
		virtual int sendMessage(const char*, std::size_t) = 0;
        virtual int getFd() const { return socket_fd;}
        virtual RecvCode getLastReadResult(std::size_t) = 0;

	protected:
		int socket_fd {0};
	};
}
#endif //SOCKET_INTERFACE_H
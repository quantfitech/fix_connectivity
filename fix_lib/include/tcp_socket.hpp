#ifndef TCP_SOCKET_H
#define TCP_SOCKET_H

#include "writer.hpp"
#include "socket_interface.hpp"

namespace qffixlib {

	class TCPSocket : public SocketInterface {
	public:
		TCPSocket();
		virtual ~TCPSocket() = default;
		bool openConnection(const std::string& host, int port) override;
		void closeConnection() override;
        int onWrite() override;
		
        int receiveMessage(char*, std::size_t, std::size_t) override;
		int sendMessage(const char*, std::size_t) override;
		
        RecvCode getLastErrorNoRead(std::size_t);

	private:
		//int socket_fd {0};
	};
}
#endif //TCP_SOCKET_H
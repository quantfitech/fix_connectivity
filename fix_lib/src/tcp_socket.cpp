#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include "tcp_socket.hpp"
#include "logger.hpp"

namespace qffixlib {

	bool TCPSocket::openConnection(const std::string& host, int port) {
		struct sockaddr_in server_address;

		if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
			LOG_ERROR("Socket creation error");
			return false;
		}
        int flags = fcntl(socket_fd, F_GETFL, 0);
        fcntl(socket_fd, F_SETFL, flags | O_NONBLOCK);

		LOG_INFO("created fd={} for {}:{}", socket_fd, host, port);

		server_address.sin_family = AF_INET;
		server_address.sin_port = htons(port);

		if (inet_pton(AF_INET, host.c_str(), &server_address.sin_addr) <= 0) {
			LOG_ERROR("Invalid address/Address {}:{}", host, port);
			return false;
		}

		if (connect(socket_fd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
			LOG_ERROR("Connection failed {}:{}", host, port);
			return false;
		}

		//LOG_INFO("connected fd={}", socket_fd);
        return true;
		
	}

	void TCPSocket::closeConnection() {
		close(socket_fd);
	}

	int TCPSocket::sendMessage(const char* data, std::size_t length) {
		return send(socket_fd, data, length, 0);
	}

    int TCPSocket::onWrite() {
        return 1;
    }

    int TCPSocket::receiveMessage(char* buffer, std::size_t offset, std::size_t remaining) {
       return recv(socket_fd, buffer + offset, remaining - 1, 0);
    }

    RecvCode TCPSocket::getLastErrorNoRead(std::size_t) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return RecvCode::WOULD_BLOCK;
        }
        return RecvCode::ERROR;
    }

}
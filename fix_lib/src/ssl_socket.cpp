#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include "ssl_socket.hpp"
#include "logger.hpp"

namespace qffixlib {


	bool SSLSocket::openConnection(const std::string& host, int port) {
		 // Initialize OpenSSL
        SSL_library_init();
        SSL_load_error_strings();
        OpenSSL_add_ssl_algorithms();

        // Create SSL context
        const SSL_METHOD* method = TLS_client_method();
        ctx = SSL_CTX_new(method);
        if (!ctx) {
            LOG_ERROR("Unable to create SSL context");
            return false;
        }

        struct sockaddr_in server_address;

        if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            LOG_ERROR("Socket creation error");
            SSL_CTX_free(ctx);
            return false;
        }

        if (!BIO_socket_nbio(socket_fd, 1)) {
            LOG_ERROR("Socket non-block error");
            SSL_CTX_free(ctx);
            return false;
        }

        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(port);

        if (inet_pton(AF_INET, host.c_str(), &server_address.sin_addr) <= 0) {
            LOG_ERROR(const_cast<char*>("Invalid address/Address not supported error"));
            SSL_CTX_free(ctx);
            return false;
        }

        int ret = connect(socket_fd, (struct sockaddr*)&server_address, sizeof(server_address));
        if (ret == 0) {
            LOG_DEBUG("Connected immediately!");
        } else if (errno == EINPROGRESS) {
            LOG_DEBUG("Connection in progress, waiting...");
        } else {
            std::cerr << "connect() failed: " << strerror(errno) << "\n";
            LOG_ERROR("Connection failed error");
            SSL_CTX_free(ctx);
            return false;
        }

        // Create an SSL object and associate it with the socket
        ssl = SSL_new(ctx);
        if (!ssl) {
            LOG_ERROR("SSL creation failed");
            ERR_print_errors_fp(stderr);
            close(socket_fd);
            SSL_CTX_free(ctx);
            return false;
        }

        SSL_set_fd(ssl, socket_fd);
        return true;
	}

	void SSLSocket::closeConnection() {
		SSL_free(ssl);
        close(socket_fd);
        SSL_CTX_free(ctx);
        EVP_cleanup();
        close(socket_fd);
	}

	int SSLSocket::sendMessage(const char* data, std::size_t length) {
       if (!mWriteBuffer.isEmpty()) {
            mWriteBuffer.append(data, length);
       }

        auto nrBytesSent = SSL_write(ssl, data, length);
        if (nrBytesSent <= 0) {
            LOG_ERROR("Failed to send message");
            ERR_print_errors_fp(stderr);
            throw std::runtime_error("failed to send");
        } else if (nrBytesSent == static_cast<int>(length)) {
            LOG_INFO("Message sent: {}", std::string(data, length));
        }
        return nrBytesSent;
	}

    int SSLSocket::receiveMessage(char* buffer, std::size_t offset, std::size_t remaining) {
        return SSL_read(ssl, buffer + offset, remaining - 1);
    }

    void SSLSocket::onConnected() {
        isConnecting = false;
    }

    int SSLSocket::onWrite() {
        if (isConnecting) {
            usleep(1000); // ugly but speeds up connection process
            return SSL_connect(ssl);
        } else {
            if (!mWriteBuffer.isEmpty()) {
                auto nrBytesSent = SSL_write(ssl, mWriteBuffer.data(), mWriteBuffer.size());
                if (nrBytesSent <= 0) {
                    LOG_ERROR("Failed to send message");
                    ERR_print_errors_fp(stderr);
                    throw std::runtime_error("failed to send");
                }
                //wipe out sent data
                mWriteBuffer.shrink(nrBytesSent);
                return mWriteBuffer.size();
            }
            return 0;
        }
    }

    RecvCode SSLSocket::getLastReadResult(std::size_t bytes) {
        int err = SSL_get_error(ssl, bytes);
        switch (err)
        {
            case SSL_ERROR_NONE:
            {
                return RecvCode::NO_ERROR;
            }
            case SSL_ERROR_ZERO_RETURN: 
            {
                return RecvCode::ERROR;
            }
            case SSL_ERROR_WANT_READ: 
            {
                return RecvCode::WOULD_BLOCK;
            }
            default:
            {
                return RecvCode::WOULD_BLOCK;
            }
        }
    }

}
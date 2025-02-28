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

    /*int wait_for_connection(int sock) {
        fd_set write_fds;
        FD_ZERO(&write_fds);
        FD_SET(sock, &write_fds);

        struct timeval timeout;
        timeout.tv_sec = 5;  // 5 seconds timeout
        timeout.tv_usec = 0;

        int ret = select(sock + 1, nullptr, &write_fds, nullptr, &timeout);
        if (ret > 0) {
            int err;
            socklen_t len = sizeof(err);
            getsockopt(sock, SOL_SOCKET, SO_ERROR, &err, &len);
            if (err == 0) {
                LOG_INFO("Connection established!");
                return 0;  // Success
            } else {
                LOG_INFO("Connection failed: {}", strerror(err));
                return -1;
            }
        } else if (ret == 0) {
            LOG_INFO("Connection timed out");
            return -1;
        } else {
            LOG_INFO("select() failed: {}",strerror(errno));
            return -1;
        }
    }*/


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
            //ERR_print_errors_fp(stderr);
            //exit(EXIT_FAILURE);
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
            /*if (wait_for_connection(socket_fd) != 0) {
                LOG_ERROR("Connection failed error");
                SSL_CTX_free(ctx);
                    return false;
            }*/
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

        /*
        while (true) {
            // Perform SSL handshake
            int ret = SSL_connect(ssl);
             if (ret == 1) {
                std::cout << "SSL handshake successful!\n";
                break;
            }
            int err = SSL_get_error(ssl, ret);
            if (err == SSL_ERROR_WANT_READ || err == SSL_ERROR_WANT_WRITE) {
                std::cout << "Waiting for read...\n";
                usleep(1000); // Simulate event-driven polling (use epoll in real cases)
                continue;
            }
            LOG_ERROR("SSL handshake failed");
            ERR_print_errors_fp(stderr);
            SSL_free(ssl);
            close(socket_fd);
            SSL_CTX_free(ctx);
            return false;
        }*/
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
        /*if (mOverflowOffset > 0) {
            if (mOverflowOffset + length >= MAX_OVERFLOW_BUFFER) {
                throw std::runtime_error("overflow buffer is full");
            }
            std::memcpy(mOverflowBuffer + mOverflowOffset, data, length);
            mOverflowOffset += length;
            return length;
        }*/
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
            /*if (mOverflowOffset > 0) {
                auto nrBytesSent = SSL_write(ssl, mOverflowBuffer, mOverflowOffset);
                if (nrBytesSent <= 0) {
                    LOG_ERROR("Failed to send message");
                    ERR_print_errors_fp(stderr);
                    throw std::runtime_error("failed to send");
                }
                //wipe out sent data
                size_t length = mOverflowOffset - nrBytesSent;
                if (length > 0) {
                    memmove(mOverflowBuffer, mOverflowBuffer + nrBytesSent, length);
                }
                mOverflowOffset -= nrBytesSent;
                return mOverflowOffset;
            }*/
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
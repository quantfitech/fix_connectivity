#ifndef SENDING_BUFFER_HPP
#define SENDING_BUFFER_HPP

#include <string>
#include <charconv>

namespace qffixlib {

    class SendingBuffer {
        public:

        char data[1024];
        size_t offset{0};
        size_t bodyLengthEnd{0};
        size_t bodyLengthValueBegin{0};

        void reset() {
            offset = 0;
            bodyLengthEnd = 0;
            bodyLengthValueBegin = 0;
        }

        void set(char aChar) {
            *(current()) = aChar;
            offset += 1;
        }

        void bodyLength() {
            bodyLengthEnd = offset;
        }

        void bodyValueBegin() {
            bodyLengthValueBegin = offset;
        }
        
        void set(int64_t value) {
            auto [ptr, ec] = std::to_chars(current(), end(), value);

            if (ec != std::errc()) {
                throw std::runtime_error("failed to copy tag to buffer");
            }
            offset = ptr - data;

            if (current() >= end()) {
                throw std::runtime_error("failed to copy tag to buffer");
            }
        }

        void set(int value) {
            auto [ptr, ec] = std::to_chars(current(), end(), value);

            if (ec != std::errc()) {
                throw std::runtime_error("failed to copy tag to buffer");
            }
            offset = ptr - data;

            if (current() >= end()) {
                throw std::runtime_error("failed to copy tag to buffer");
            }
        }

        void setBodyLength() {
            size_t bodyLength = offset - bodyLengthEnd;
            if (bodyLength < 0 || bodyLength > 999) {   
                throw std::runtime_error("invalid body length");
            }
            auto boyLengthFormatted = std::format("{:03}", bodyLength);
            std::memcpy(data + bodyLengthValueBegin, boyLengthFormatted.data(), boyLengthFormatted.length());
        }

        int checkSum() {
            return std::reduce(begin(), current(), 0) % 256;
        }

        size_t length() { return offset; }
        char* begin() { return  data; }
        char* current() { return  data + offset; }
        char* end() {return data + 1023; }
    };
}


#endif //SENDING_BUFFER_HPP
#ifndef SENDING_BUFFER_HPP
#define SENDING_BUFFER_HPP

#include <string>
#include <charconv>
#include <cstring>
#include <numeric> 

namespace qffixlib {

    class SendingBuffer {
    private:
        static const unsigned BUFFER_SIZE = 8192;
        char mData[BUFFER_SIZE];
        size_t mOffset{0};
        size_t mBodyLengthEnd{0};
        size_t mBodyLengthValueBegin{0};

    public:
        void reset() {
            mOffset = 0;
            mBodyLengthEnd = 0;
            mBodyLengthValueBegin = 0;
        }

        void advance(size_t size) {
            if (mOffset + size >= BUFFER_SIZE) {
                throw std::runtime_error("advance out of size!");
            }
            mOffset += size;
            }

        void append(const std::string& data) {
            if (mOffset + data.length() >= BUFFER_SIZE) {
                throw std::runtime_error("append out of size!");
            }
            std::memcpy(current(), data.data(), data.length());
            mOffset += data.length();
        }


        void set(char aChar) {
            if (mOffset + 1 >= BUFFER_SIZE) {
                throw std::runtime_error("set out of size!");
            }
            *(current()) = aChar;
            mOffset += 1;
        }

        void bodyLength() {
            mBodyLengthEnd = mOffset;
        }

        void bodyValueBegin() {
            mBodyLengthValueBegin = mOffset;
        }
        
        void set(int64_t value) {
            auto [ptr, ec] = std::to_chars(current(), end(), value);

            if (ec != std::errc()) {
                throw std::runtime_error("failed to copy tag to buffer");
            }
            mOffset = ptr - mData;

            if (current() >= end()) {
                throw std::runtime_error("failed to copy tag to buffer");
            }
        }

        void set(int value) {
            auto [ptr, ec] = std::to_chars(current(), end(), value);

            if (ec != std::errc()) {
                throw std::runtime_error("failed to copy tag to buffer");
            }
            mOffset = ptr - mData;

            if (current() >= end()) {
                throw std::runtime_error("failed to copy tag to buffer");
            }
        }

        void setBodyLength() {
            size_t bodyLength = mOffset - mBodyLengthEnd;
            if (bodyLength > 999) {   
                throw std::runtime_error("invalid body length");
            }
            auto boyLengthFormatted = std::format("{:03}", bodyLength);
            std::memcpy(mData + mBodyLengthValueBegin, boyLengthFormatted.data(), boyLengthFormatted.length());
        }

        int checkSum() {
            return std::reduce(begin(), current(), 0) % 256;
        }

        size_t length() { return mOffset; }
        char* begin() { return  mData; }
        char* current() { return  mData + mOffset; }
        char* end() {return mData + 1023; }
    };
}


#endif //SENDING_BUFFER_HPP
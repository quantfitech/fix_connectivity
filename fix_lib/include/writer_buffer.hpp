#ifndef WRITER_BUFFER_H
#define WRITER_BUFFER_H

#include <iostream>
#include <deque>
#include <vector>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

namespace qffixlib {

    class WriterBuffer {
    private:
        static constexpr int MAX_OVERFLOW_BUFFER = 8192;
        char mOverflowBuffer[MAX_OVERFLOW_BUFFER];
		size_t mOverflowOffset{0};

    public:

        char* data() { return mOverflowBuffer; }

        size_t size() { return mOverflowOffset; }

        bool isEmpty() { return mOverflowOffset == 0; }
        
        void append(const char* data, size_t length) {
            if (mOverflowOffset + length >= MAX_OVERFLOW_BUFFER) {
                throw std::runtime_error("writer buffer is full");
            }
            std::memcpy(mOverflowBuffer + mOverflowOffset, data, length);
            mOverflowOffset += length;
        }

        void shrink(size_t to_remove) {
            if (to_remove > mOverflowOffset) {
                throw std::runtime_error("shrinking more then possible");
            }
            size_t length = mOverflowOffset - to_remove;
            if (length > 0) {
                    memmove(mOverflowBuffer, mOverflowBuffer + to_remove, length);
                }
                mOverflowOffset -= to_remove;
        }
        
    };
}

#endif //WRITER_BUFFER_H
#ifndef READER_BUFFER_H
#define READER_BUFFER_H

#include <iostream>
#include <deque>
#include <vector>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

namespace qffixlib {

    using BufferIt = std::vector<char>::iterator;

    class ReaderBuffer {
    private:
        int MAX_BUFFER_SIZE{8192};
        std::vector<char> mBuffer;
		size_t mOffset{0};

    public:

        ReaderBuffer() { mBuffer.reserve(MAX_BUFFER_SIZE); }

        char* data() { return mBuffer.data(); }

        BufferIt begin() { return mBuffer.begin(); }

        size_t offset() { return mOffset; }

        size_t remaining();
        
        void append(int length) { mOffset += static_cast<size_t>(length); }

        bool consume(int consumed);

        std::pair<BufferIt, BufferIt> tryGetTag(const std::string&, BufferIt);
    };
}

#endif //READER_BUFFER_H
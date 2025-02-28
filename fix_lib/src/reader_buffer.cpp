    #include "reader_buffer.hpp"
    #include "logger.hpp"
    #include "fix_types.hpp"

    namespace qffixlib {

    size_t ReaderBuffer::remaining() {
        auto remaining =  MAX_BUFFER_SIZE - mOffset; 
        if (remaining < 1024) {
            MAX_BUFFER_SIZE *= 2;
            mBuffer.resize(MAX_BUFFER_SIZE);
            remaining = MAX_BUFFER_SIZE - mOffset;
        }
        return remaining;
    }

    bool ReaderBuffer::consume(int consumed) {
        if (static_cast<size_t>(consumed) > mOffset) {
            throw std::runtime_error("consumed more than avaialbe!");
        }
        else if (static_cast<size_t>(consumed) == mOffset) {
            mOffset = 0;
            return false;
        }
        std::move(mBuffer.begin() + consumed, mBuffer.begin() + mOffset, mBuffer.begin());
        mOffset -= consumed;
        return true;
    }

    std::pair<BufferIt, BufferIt> ReaderBuffer::tryGetTag(const std::string& tag, BufferIt begin) {
        auto end = mBuffer.begin() + mOffset;

		LOG_DEBUG("EXTRACT {}", std::string(mBuffer.begin(), end));

		auto it_begin = std::search(begin, end, tag.begin(), tag.end());
		if (it_begin == end) { return std::make_pair(end, end); }

        it_begin += tag.length();

        auto it_end = std::find(it_begin, end, SOH);  // Find end of tag value
		if (it_end == end) { return std::make_pair(end, end); } 

        return std::make_pair(it_begin, it_end);
    }

    }

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
		//std::string begin = "8=";
		auto it_begin = std::search(begin, end, tag.begin(), tag.end());
		if (it_begin == end) { return std::make_pair(end, end); }

        it_begin += tag.length();

        auto it_end = std::find(it_begin, end, SOH);  // Find end of tag value
		if (it_end == end) { return std::make_pair(end, end); } 

        return std::make_pair(it_begin, it_end);
    }

/*
        void StreamBuffer::append(const char* data, size_t len) {
            mBuffer.insert(mBuffer.end(), data, data + len);
        }

        // Find FIX tag (e.g., "9=" for body length)
        int StreamBuffer::findTagValue(const std::string& tag) {
            std::string tagSearch = tag + "=";
            auto it = std::search(mBuffer.begin(), mBuffer.end(), tagSearch.begin(), tagSearch.end());

            if (it != mBuffer.end()) {
                auto start = it + tagSearch.size();
                auto end = std::find(start, mBuffer.end(), SOH);  // Find end of tag value
                if (end != mBuffer.end()) {
                    return std::stoi(std::string(start, end));
                }
            }
            return -1;  // Not found
        }

        // Extract full FIX messages
        bool StreamBuffer::extractMessage(std::string& outMessage) {
            auto it = std::find(mBuffer.begin(), mBuffer.end(), SOH);
            if (it == mBuffer.end()) return false;  // No complete message

            //int bodyLength = findTagValue("9");
            std::string tagSearch = "9=";
            it = std::search(mBuffer.begin(), mBuffer.end(), tagSearch.begin(), tagSearch.end());
            if (it == mBuffer.end()) { return false; }
             
            auto start = it + tagSearch.size();
            auto end = std::find(start, mBuffer.end(), SOH);  // Find end of tag value
            if (end == mBuffer.end()) { return false;} 

            auto bodyLength = std::stoi(std::string(start, end));
            if (bodyLength == -1) return false;  // Can't determine message length

            std::cout << "body length: " << bodyLength << std::endl;


            // Approximate message length (header + body + checksum)
            size_t messageLength = std::distance(mBuffer.begin(), end) + 1 + bodyLength + 7;
            if (mBuffer.size() < messageLength) return false;  // Not enough data

            std::cout << "msg length: " << messageLength << std::endl;
            outMessage.assign(mBuffer.begin(), mBuffer.begin() + messageLength);
            std::cout << "msg: " << outMessage << std::endl;
            mBuffer.erase(mBuffer.begin(), mBuffer.begin() + messageLength);  // Remove consumed message
            return true;
        }
        */
    }

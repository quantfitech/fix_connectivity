#ifndef TOKEN_ITERATOR_HPP
#define TOKEN_ITERATOR_HPP

namespace qffixlib {

    #include <string>
    #include <charconv>
    #include <iostream>
    
    class TokenIterator {
        static constexpr const char VALUE_SEPARATOR = '=';
        static constexpr const char FIELD_SEPARATOR = '\01'; //'|'; //

        struct TokenData {
            int tag={0};
            const char* data{nullptr};
            long length{0};
        };

    public:
    
        using pointer = const TokenData*;
        using reference = const TokenData&;

        // Construct from a stream and delimiter.
        TokenIterator(const char* data, size_t length)
            : mData(data), mLength(length)
        {
            mEnd = mData + mLength;
            mCurrent = mData;
            ++(*this); // Read the first token
        }

        // Pre-increment: read next token from the stream.
        TokenIterator& operator++() {

            if (mCurrent != mEnd)
            {
                //std::cout << " curr - data " << mCurrent - mData << " end - curr " << mEnd - mCurrent << std::endl;
                //std::cout << "remaining (" << std::string(mCurrent, mEnd - mCurrent -1) << ")" <<  std::endl;
                if ((mEnd - mCurrent) == 1) {
                    mCurrentToken = {};
                    mCurrent = mEnd = nullptr;
                    return *this;
                }
                const auto* equals = std::find(mCurrent, mEnd, VALUE_SEPARATOR);

                if (equals == mEnd) {
                    std::cout << "no value separator in {}" << std::string(mCurrent, mEnd - mCurrent -1) << std::endl;
                    mCurrentToken = {};
                    mCurrent = mEnd = nullptr;
                    return *this;
                }

                int tag = 0;
                
                auto [ptr, ec] = std::from_chars(mCurrent, equals, tag);
                
                if (ec != std::errc()) {
                    throw std::out_of_range(std::string(mCurrent, equals) + " is not a valid field tag");
                }
                const auto* delimiter = std::find(equals + 1, mEnd, FIELD_SEPARATOR);

                if (delimiter == mEnd && *delimiter != FIELD_SEPARATOR) {
                    mCurrentToken = {};
                    mCurrent = mEnd = nullptr;
                    return *this;
                }
                //auto raw_length = delimiter - mCurrent + 1;
                mCurrentToken = {tag, equals + 1, delimiter - equals - 1};
                //std::cout << mEnd - delimiter << std::endl;
                if (delimiter != mEnd) {
                    mCurrent = delimiter + 1;                
                } else {
                    mCurrentToken = {};
                    mCurrent = mEnd = nullptr;
                }
            }
            return *this;
        }


        // Post-increment.
        TokenIterator operator++(int) {
            TokenIterator temp(*this);
            ++(*this);
            return temp;
        }

        // Dereference returns the current token.
        reference operator*() const { return mCurrentToken; }
        pointer operator->() const { return &mCurrentToken; }

        // Equality: two iterators are equal if they have the same stream pointer.
        bool operator==(const TokenIterator& other) const {
            return mData == other.mData;
        }
        bool operator!=(const TokenIterator& other) const {
            return !(*this == other);
        }

    private:
        const char* mData{nullptr};
        size_t mLength{0};
        const char* mEnd{nullptr};
        const char* mCurrent{nullptr};
        TokenData mCurrentToken{};
    };

}

#endif //TOKEN_ITERATOR_HPP
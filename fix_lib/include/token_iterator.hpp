#ifndef TOKEN_ITERATOR_HPP
#define TOKEN_ITERATOR_HPP

#include <string>
#include <charconv>
#include <iostream>

namespace qffixlib {
    
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
        TokenIterator& operator++();

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

        std::string getString() { return std::string(mData, mLength); }

    private:
        const char* mData{nullptr};
        size_t mLength{0};
        const char* mEnd{nullptr};
        const char* mCurrent{nullptr};
        TokenData mCurrentToken{};
    };

}

#endif //TOKEN_ITERATOR_HPP
  
  
  #include "token_iterator.hpp"
  #include "logger.hpp"

  namespace qffixlib {

    TokenIterator& TokenIterator::operator++() {

        if (mCurrent != mEnd)
        {
            //LOG_DEBUG(" curr - data = {}  end - curr = {} ", (size_t)(mCurrent - mData), (size_t)(mEnd - mCurrent));
            if ((mEnd - mCurrent) == 1) {
                LOG_DEBUG(" curr - data = {}  end - curr = {} ", (size_t)(mCurrent - mData), (size_t)(mEnd - mCurrent));
                mCurrentToken = {};
                mCurrent = mEnd = nullptr;
                return *this;
            }
            const auto* equals = std::find(mCurrent, mEnd, VALUE_SEPARATOR);

            if (equals == mEnd) {
                LOG_WARN("no value separator in {}", std::string(mCurrent, mEnd - mCurrent -1));
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
                LOG_WARN("no field separator in {}", std::string(mCurrent, mEnd - mCurrent -1));
                mCurrentToken = {};
                mCurrent = mEnd = nullptr;
                return *this;
            }

            mCurrentToken = {tag, equals + 1, delimiter - equals - 1};
            if (delimiter != mEnd) {
                mCurrent = delimiter + 1;                
            } else {
                LOG_DEBUG(" curr - data = {}  end - curr = {} ", (size_t)(mCurrent - mData), (size_t)(mEnd - mCurrent));
                mCurrentToken = {};
                mCurrent = mEnd = nullptr;
            }
        }
        return *this;
    }
  }

#ifndef FIX_MESSAGE_HPP
#define FIX_MESSAGE_HPP

#include "fix_group.hpp"
#include "fix_header.hpp"
//#include "logger.hpp"


namespace qffixlib {

    using Trailer = FieldT<FIX::Tag::CheckSum, std::string>;


    // FIXMessage definition:
    template <char MsgTypeChar, typename... Fields>
    class FIXMessage : public BaseMessage<Fields...> {
        public:
        FIXMessage() = default;
        FIXMessage(Header* header): mHeader(header) { 
            mHeader->set<FIX::Tag::MsgType>(MsgType);
        }

        char MsgType = MsgTypeChar;

        Header* mHeader{nullptr};

        Trailer mTrailer;

        public:
       
        void deserialize(TokenIterator& iter) {
            // Using a fold expression to expand over the tuple elements.
            mHeader->deserialize(iter);
            std::apply([&iter](auto&... elems) { ((elems.deserialize(iter)), ...); }, this->fields);
            mTrailer.deserialize(iter);
            if (!mTrailer.isSet) {
                //LOG_WARN("deserialize failed for msg {}, stuck on {}, trailer not reached!", MsgType, iter->tag);
                std::cout << "deserialize failed for msg {}, stuck on {}, trailer not reached!" << std::endl;
            }
        }

        void serialize( SendingBuffer& buff) const {
            // Using a fold expression to expand over the tuple elements.
            mHeader->serialize(buff);
            std::apply([&buff](auto&... elems) { ((elems.serialize(buff)), ...); }, this->fields);
            mTrailer.serialize(buff);
        }

    };

}

#endif //FIX_MESSAGE_HPP

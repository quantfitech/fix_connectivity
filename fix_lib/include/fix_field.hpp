#ifndef FIX_FIELD_HPP
#define FIX_FIELD_HPP

#include <string>

#include <iostream>
#include <tuple>
#include <sstream>
#include <string>

#include <iostream>
#include <tuple>
#include <string>
#include <sstream>

#include "utils.hpp"
#include "sending_buffer.hpp"
#include "token_iterator.hpp"
#include "lexical_cast.hpp"

namespace qffixlib {

    static constexpr const char VALUE_SEPARATOR = '=';
	static constexpr const char FIELD_SEPARATOR = '\01'; // '|';
    static constexpr const char DOUBLE_PRECISION = 9;


    template <int Tag, typename Type>
    struct FieldT {

        static constexpr int tag = Tag;
        Type value;

        FieldT() = default;
        explicit FieldT(Type t) : value(t) {}
        using ValueType = Type;

        bool isSet{false};

        void setValue(Type val) {
            value = val;
            isSet = true; 
        }


        void serialize(SendingBuffer& buff) const {   
            throw std::runtime_error("undefined field type");
            if (!isSet) {
                return;
            }

            buff.set(tag);

            buff.set(VALUE_SEPARATOR);

            buff.set(FIELD_SEPARATOR);
        }

        void deserialize(TokenIterator& iter) {
            throw std::runtime_error("undefined field type");
            if ((*iter).tag == tag) {
                setValue(LexicalCast<Type>::cast((*iter).data, (*iter).length));
                ++iter;
            }
        }
    };

    template <int Tag>
    struct FieldT<Tag,char> {
        using ValueType = char;
        static constexpr int tag = Tag;
        ValueType value;

        FieldT() = default;
        explicit FieldT(ValueType t) : value(t) {}
        

        bool isSet{false};

        void setValue(ValueType val) {
            value = val;
            isSet = true; 
        }

        void serialize(SendingBuffer& buff) const {   
            if (!isSet) {
                return;
            }

            buff.set(tag);

            buff.set(VALUE_SEPARATOR);
            
            buff.set(value);

            buff.set(FIELD_SEPARATOR);

        }

        void deserialize(TokenIterator& iter) {
            if ((*iter).tag == tag) {
                setValue((*iter).data[0]);
                ++iter;
            }
        }
    };

    template <int Tag>
    struct FieldT<Tag,std::string> {
        using ValueType = std::string;
        static constexpr int tag = Tag;
        ValueType value;

        FieldT() = default;
        explicit FieldT(const ValueType& t) : value(t) {}
       

        bool isSet{false};

        void setValue(const ValueType& val) {
            value = val;
            isSet = true; 
        }

        void setValue(ValueType&& val) {
            value = std::move(val);
            isSet = true; 
        }

         void serialize(SendingBuffer& buff) const {   
            if (tag == FIX::Tag::CheckSum) {

                buff.setBodyLength();

                auto checkSum = std::format("{:03}", buff.checkSum());

                buff.set(tag);

                buff.set(VALUE_SEPARATOR);

                buff.append(checkSum);

                buff.set(FIELD_SEPARATOR);
                return;
            }
            if (!isSet){
                return;
            }

            buff.set(tag);

            buff.set(VALUE_SEPARATOR);

            if(tag == FIX::Tag::BodyLength) {
                buff.bodyValueBegin();
            }

            buff.append(value);

            buff.set(FIELD_SEPARATOR);

            if(tag == FIX::Tag::BodyLength) {
                buff.bodyLength();
            }
        }

        void deserialize(TokenIterator& iter) {
            if ((*iter).tag == tag) {
                setValue(std::string((*iter).data, (*iter).length));
                ++iter;
            }
        }
    };

    template <int Tag>
    struct FieldT<Tag,int64_t> {
         using ValueType = int64_t;
        static constexpr int tag = Tag;
        ValueType value;

        FieldT() = default;
        explicit FieldT(ValueType t) : value(t) {}
       

        bool isSet{false};

        void setValue(ValueType val) {
            value = val;
            isSet = true; 
        }

         void serialize(SendingBuffer& buff) const {   
            if (!isSet) {
                return;
            }

            buff.set(tag);

            buff.set(VALUE_SEPARATOR);
            
            buff.set(value);

            buff.set(FIELD_SEPARATOR);
        }

        void deserialize(TokenIterator& iter) {
            if ((*iter).tag == tag) {
                setValue(LexicalCast<ValueType>::cast((*iter).data, (*iter).length));
                ++iter;
            }
        }
    };


    template <int Tag>
    struct FieldT<Tag,bool> {
        using ValueType = bool;
        static constexpr int tag = Tag;
        ValueType value;

        FieldT() = default;
        explicit FieldT(ValueType t) : value(t) {}
       

        bool isSet{false};

        void setValue(ValueType val) {
            value = val;
            isSet = true; 
        }

         void serialize(SendingBuffer& buff) const {   
            if (!isSet) {
                return;
            }

            buff.set(tag);

            buff.set(VALUE_SEPARATOR);
            
            buff.set(value ? 'Y' : 'N');

            buff.set(FIELD_SEPARATOR);

        }

        void deserialize(TokenIterator& iter) {
            if ((*iter).tag == tag) {
                setValue(LexicalCast<ValueType>::cast((*iter).data, (*iter).length));
                ++iter;
            }
        }
    };

    template <int Tag>
    struct FieldT<Tag,double> {
        using ValueType = double;
        static constexpr int tag = Tag;
        double value;

        FieldT() = default;
        explicit FieldT(ValueType t) : value(t) {}

        bool isSet{false};

        void setValue(ValueType val) {
            value = val;
            isSet = true; 
        }

         void serialize(SendingBuffer& buff) const {   
            if (!isSet) {
                return;
            }

            buff.set(tag);

            buff.set(VALUE_SEPARATOR);
            
            auto length = modp_dtoa(value, buff.current(), DOUBLE_PRECISION);
            buff.advance(length);

            buff.set(FIELD_SEPARATOR);

        }

        void deserialize(TokenIterator& iter) {
            if ((*iter).tag == tag) {
                setValue(LexicalCast<ValueType>::cast((*iter).data, (*iter).length));
                ++iter;
            }
        }
    };

    template <int Tag>
    struct FieldT<Tag,FIX::UTCTimestamp> {
        using ValueType = FIX::UTCTimestamp;
        static constexpr int tag = Tag;
        ValueType value;

        FieldT() = default;
        explicit FieldT(const ValueType& t) : value(t) {}
        

        std::string rawValue;

        bool isSet{false};

        void setValue(ValueType&& val) {
            value = val;
            isSet = true; 
        }

        void setRawValue(const std::string& val) {
            rawValue = val;
            isSet = true; 
        }

         void serialize(SendingBuffer& buff) const {   
            if (!isSet) {
                return;
            }

            buff.set(tag);

            buff.set(VALUE_SEPARATOR);
            
            if (rawValue.empty()) {
                std::time_t time = std::chrono::system_clock::to_time_t(value);
                // Convert time_t to tm (UTC/GMT time)
                std::tm tm = *std::gmtime(&time);

                // Format the tm structure into a string
                std::ostringstream oss;
                oss << std::put_time(&tm, "%Y%m%d %H:%M:%S");

                // Extract milliseconds from the time_point
                auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
                    value.time_since_epoch()
                ) % 1000;

                // Append milliseconds to the string
                oss << "." << std::setfill('0') << std::setw(3) << milliseconds.count();
                buff.append(oss.str());
            }

            buff.set(FIELD_SEPARATOR);

        }

        void deserialize(TokenIterator& iter) {
            if ((*iter).tag == tag) {
                setValue(LexicalCast<ValueType>::cast((*iter).data, (*iter).length));
                ++iter;
            }
        }
    };

    template <int Tag>
    struct FieldT<Tag,FIX::UTCDate> {
        using ValueType = FIX::UTCDate;
        static constexpr int tag = Tag;
        ValueType value;

        FieldT() = default;
        explicit FieldT(const ValueType& t) : value(t) {}
        

        std::string rawValue;

        bool isSet{false};

        void setValue(const ValueType& val) {
            value = val;
            isSet = true; 
        }

        void setRawValue(const std::string& val) {
            rawValue = val;
            isSet = true; 
        }

         void serialize(SendingBuffer& buff) const {   
            if (!isSet) {
                return;
            }

            buff.set(tag);

            buff.set(VALUE_SEPARATOR);
            
            if (rawValue.empty()) {
                std::tm tm = *std::localtime(&value.mDate);
                std::ostringstream oss;
                oss << std::put_time(&tm, "%Y-%m-%d");
                std::string date = oss.str();
                rawValue = date;
            }
            buff.append(rawValue);

            buff.set(FIELD_SEPARATOR);
        }

        void deserialize(TokenIterator& iter) {
            if ((*iter).tag == tag) {
                setValue(LexicalCast<ValueType>::cast((*iter).data, (*iter).length));
                ++iter;
            }
        }
    };

    template <int Tag>
    struct FieldT<Tag,FIX::UTCTimeOnly> {
        using ValueType = FIX::UTCTimeOnly;
        static constexpr int tag = Tag;
        ValueType value;

        FieldT() = default;
        explicit FieldT(const ValueType& t) : value(t) {}

        std::string rawValue;

        bool isSet{false};

        void setValue(ValueType val) {
            value = val;
            isSet = true; 
        }

        void setRawValue(const std::string& val) {
            rawValue = val;
            isSet = true; 
        }

         void serialize(SendingBuffer& buff) const {   
            if (!isSet) {
                return;
            }

            buff.set(tag);

            buff.set(VALUE_SEPARATOR);
            
            if (rawValue.empty()) {
                std::tm tm = *std::localtime(&value.mTime);
                std::ostringstream oss;
                oss << std::put_time(&tm, "%H:%M:%S");
                std::string time = oss.str();
                rawValue = time;
            }

            buff.append(rawValue);

            buff.set(FIELD_SEPARATOR);
        }

        void deserialize(TokenIterator& iter) {
            if ((*iter).tag == tag) {
                setValue(LexicalCast<ValueType>::cast((*iter).data, (*iter).length));
                ++iter;
            }
        }
    };

}

#endif

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
            if (!isSet) {
                return;
            }

            buff.set(tag);

            buff.set(VALUE_SEPARATOR);

            buff.set(FIELD_SEPARATOR);

        }

        void deserialize(TokenIterator& iter) {
            std::cout << " undef tag " << tag << " iter tag " << iter->tag << std::endl;
            if ((*iter).tag == tag) {
                setValue(LexicalCast<Type>::cast((*iter).data, (*iter).length));
                ++iter;
            }
        }
    };

    template <int Tag>
    struct FieldT<Tag,char> {

        static constexpr int tag = Tag;
        char value;

        FieldT() = default;
        explicit FieldT(char t) : value(t) {}
        using ValueType = char;

        bool isSet{false};

        void setValue(char val) {
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
            //std::cout << " char tag " << tag << " iter tag " << iter->tag << std::endl;
            if ((*iter).tag == tag) {
                setValue((*iter).data[0]);
                ++iter;
            }
        }
    };

    template <int Tag>
    struct FieldT<Tag,std::string> {

        static constexpr int tag = Tag;
        std::string value;

        FieldT() = default;
        explicit FieldT(const std::string& t) : value(t) {}
        using ValueType = std::string;

        bool isSet{false};

        void setValue(const std::string& val) {
            value = val;
            isSet = true; 
        }

        void setValue(std::string&& val) {
            value = std::move(val);
            isSet = true; 
        }

         void serialize(SendingBuffer& buff) const {   
            if (tag == FIX::Tag::CheckSum) {

                buff.setBodyLength();

                auto checkSum = std::format("{:03}", buff.checkSum());

                buff.set(tag);

                buff.set(VALUE_SEPARATOR);

                std::memcpy(buff.current(), checkSum.data(), checkSum.length());
                buff.offset += checkSum.length();

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
            
            std::memcpy(buff.current(), value.data(), value.length());
            buff.offset += value.length();

            buff.set(FIELD_SEPARATOR);

            if(tag == FIX::Tag::BodyLength) {
                buff.bodyLength();
            }
        }

        void deserialize(TokenIterator& iter) {
             //std::cout << " string tag " << tag << " iter tag " << iter->tag << std::endl;
            if ((*iter).tag == tag) {
                setValue(std::string((*iter).data, (*iter).length));
                ++iter;
            }
        }
    };

    template <int Tag>
    struct FieldT<Tag,int64_t> {

        static constexpr int tag = Tag;
        int64_t value;

        FieldT() = default;
        explicit FieldT(int64_t t) : value(t) {}
        using ValueType = int64_t;

        bool isSet{false};

        void setValue(int64_t val) {
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
            //std::cout << " int tag " << tag << " iter tag " << iter->tag <<std::endl;
            if ((*iter).tag == tag) {
                setValue(LexicalCast<ValueType>::cast((*iter).data, (*iter).length));
                ++iter;
            }
        }
    };


    template <int Tag>
    struct FieldT<Tag,bool> {

        static constexpr int tag = Tag;
        bool value;

        FieldT() = default;
        explicit FieldT(bool t) : value(t) {}
        using ValueType = bool;

        bool isSet{false};

        void setValue(bool val) {
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
            //std::cout << " bool tag " << tag << " iter tag " << iter->tag << std::endl;
            if ((*iter).tag == tag) {
                setValue(LexicalCast<ValueType>::cast((*iter).data, (*iter).length));
                ++iter;
            }
        }
    };

    template <int Tag>
    struct FieldT<Tag,double> {

        static constexpr int tag = Tag;
        double value;

        FieldT() = default;
        explicit FieldT(double t) : value(t) {}
        using ValueType = double;

        bool isSet{false};

        void setValue(double val) {
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
            buff.offset += length;

            buff.set(FIELD_SEPARATOR);

        }

        void deserialize(TokenIterator& iter) {
            //std::cout << " double tag " << tag << " iter tag " << iter->tag <<std::endl;
            if ((*iter).tag == tag) {
                setValue(LexicalCast<ValueType>::cast((*iter).data, (*iter).length));
                ++iter;
            }
        }
    };

    template <int Tag>
    struct FieldT<Tag,FIX::UTCTimestamp> {

        static constexpr int tag = Tag;
        FIX::UTCTimestamp value;

        FieldT() = default;
        explicit FieldT(const FIX::UTCTimestamp& t) : value(t) {}
        using ValueType = FIX::UTCTimestamp;

        std::string rawValue;

        bool isSet{false};

        void setValue(FIX::UTCTimestamp val) {
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

                std::string str_val = oss.str();

                std::memcpy(buff.current(), str_val.data(), str_val.length());
                buff.offset += str_val.length();
            }

            buff.set(FIELD_SEPARATOR);

        }

        void deserialize(TokenIterator& iter) {
            //std::cout << " utctimest tag " << tag << " iter tag " << iter->tag << std::endl;
            if ((*iter).tag == tag) {
                setValue(LexicalCast<ValueType>::cast((*iter).data, (*iter).length));
                ++iter;
            }
        }
    };

    template <int Tag>
    struct FieldT<Tag,FIX::UTCDate> {

        static constexpr int tag = Tag;
        FIX::UTCDate value;

        FieldT() = default;
        explicit FieldT(const FIX::UTCDate& t) : value(t) {}
        using ValueType = FIX::UTCDate;

        std::string rawValue;

        bool isSet{false};

        void setValue(FIX::UTCDate val) {
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

            std::memcpy(buff.current(), rawValue.data(), rawValue.length());
            buff.offset += rawValue.length();

            buff.set(FIELD_SEPARATOR);

        }

        void deserialize(TokenIterator& iter) {
            //std::cout << " date tag " << tag << " iter tag " << iter->tag << std::endl;
            if ((*iter).tag == tag) {
                setValue(LexicalCast<ValueType>::cast((*iter).data, (*iter).length));
                ++iter;
            }
        }
    };

    template <int Tag>
    struct FieldT<Tag,FIX::UTCTimeOnly> {

        static constexpr int tag = Tag;
        FIX::UTCTimeOnly value;

        FieldT() = default;
        explicit FieldT(const FIX::UTCTimeOnly& t) : value(t) {}
        using ValueType = FIX::UTCTimeOnly;

        std::string rawValue;

        bool isSet{false};

        void setValue(FIX::UTCTimeOnly val) {
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

            std::memcpy(buff.current(), rawValue.data(), rawValue.length());
            buff.offset += rawValue.length();

            buff.set(FIELD_SEPARATOR);

        }

        void deserialize(TokenIterator& iter) {
            //std::cout << " time tag " << tag << " iter tag " << iter->tag << std::endl;
            if ((*iter).tag == tag) {
                setValue(LexicalCast<ValueType>::cast((*iter).data, (*iter).length));
                ++iter;
            }
        }
    };

}

#endif

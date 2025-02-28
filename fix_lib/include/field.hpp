#ifndef FIELD_HPP
#define FIELD_HPP

#include <string>
#include <cstdint>
#include "field_value.hpp"

namespace qffixlib
{

enum class timestamp_format
{
    seconds,
    milliseconds,
    microseconds
};

std::string timestamp_string(timestamp_format format);

class Field
{
public:

    explicit Field(int tag, const qffixlib::field_value& value);
  
    explicit Field(int tag, std::string value);
    explicit Field(int tag, std::string_view value, std::size_t length);
    explicit Field(int tag, const char* value);
    explicit Field(int tag, bool value);
  
    explicit Field(int tag, int8_t value);
    explicit Field(int tag, int16_t value);
    explicit Field(int tag, int32_t value);
    explicit Field(int tag, int64_t value);

    explicit Field(int tag, uint8_t value);
    explicit Field(int tag, uint16_t value);
    explicit Field(int tag, uint32_t value);
    explicit Field(int tag, uint64_t value);

    constexpr int tag() const { return m_tag; }
    constexpr const std::string& value() const { return m_value; } 

    bool operator==(const qffixlib::field_value& other) const {
        return m_value == other.value();
    }


    bool operator<(const Field& other) const {
        return m_value < other.m_value;
    }

    bool operator==(const Field& other) const {
        return m_value == other.m_value;
    }

    std::size_t rawLength() const { return mLength; }

private:

    int m_tag{0};
    std::string m_value{""};
    std::size_t mLength{0};

};

}

#endif
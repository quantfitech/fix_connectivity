#include "field.hpp"
#include <ctime>
#include <iomanip>
#include <chrono>
//#include <boost/lexical_cast.hpp>

namespace qffixlib
{

char const * const seconds_format =  "%Y%m%d-%H:%M:%S";

std::string timestamp_string(timestamp_format format)
{
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);

    std::tm utc_tm = *std::gmtime(&now_time_t);
    std::ostringstream oss;
    oss << std::put_time(&utc_tm, seconds_format);

    std::string value = oss.str();

    switch (format)
    {
        case timestamp_format::seconds:
            break;

        case timestamp_format::milliseconds:
        {
            auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
            auto buffer = std::to_string(milliseconds.count());
            static const char* padding = "000";
            value += "." + ((padding + buffer.length()) + buffer);
            break;
        }

        case timestamp_format::microseconds:
        {
            auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()) % 1000000;
            auto buffer = std::to_string(microseconds.count());
            static const char* padding = "000000";
            value += "." + ((padding + buffer.length()) + buffer); 
            break;
        }

        default:
            throw "unsupported timestamp format " + std::to_string(static_cast<int>(format));
    };
  
    return value;
}

Field::Field(int tag, const qffixlib::field_value& value)
: m_tag(tag), m_value(value.value())
{
}

Field::Field(int tag, std::string value)
: m_tag(tag), m_value(std::move(value))
{
}

Field::Field(int tag, std::string_view value, std::size_t length)
: m_tag(tag), m_value(value), mLength(length)
{
}

Field::Field(int tag, const char* value)
: m_tag(tag), m_value(value)
{
}

Field::Field(int tag, bool value)
:   m_tag(tag), m_value(value ? std::string("Y") : std::string("N"))
{
}

Field::Field(int tag, int8_t value) 
:   m_tag(tag), m_value(std::to_string(value))
{
}

Field::Field(int tag, int16_t value) 
:   m_tag(tag), m_value(std::to_string(value))
{
}

Field::Field(int tag, int32_t value) 
:   m_tag(tag), m_value(std::to_string(value))
{
}

Field::Field(int tag, int64_t value) 
:   m_tag(tag), m_value(std::to_string(value))
{
}


Field::Field(int tag, uint8_t value) 
:   m_tag(tag), m_value(std::to_string(value))
{
}

Field::Field(int tag, uint16_t value) 
:   m_tag(tag), m_value(std::to_string(value))
{
}

Field::Field(int tag, uint32_t value) 
:   m_tag(tag), m_value(std::to_string(value))
{
}

Field::Field(int tag, uint64_t value) 
:   m_tag(tag), m_value(std::to_string(value))
{
}

}
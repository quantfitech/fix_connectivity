#ifndef LEXICAL_CAST_HPP
#define LEXICAL_CAST_HPP

#include <iostream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <charconv>
#include <cmath>
#include "tag.hpp"


namespace qffixlib {

    template<typename T> struct LexicalCast
    {
        static T cast(const char*, size_t)
        {
            static_assert("Undefined FIC type");
            return {};
        }
    };

    template<>
    struct LexicalCast<std::string>
    {
        static std::string cast(const char* offset, size_t size)
        {
            return {offset, size};
        }
    };

    template<>
    struct LexicalCast<double>
    {
        static double cast(const char* offset, size_t /*size*/)
        {
            double r = 0.0;
            bool neg = false;
            if (*offset == '-') {
                neg = true;
                ++offset;
            }
            while (*offset >= '0' && *offset <= '9') {
                r = (r*10.0) + (*offset - '0');
                ++offset;
            }
            if (*offset == '.') {
                double f = 0.0;
                int n = 0;
                ++offset;
                while (*offset >= '0' && *offset <= '9') {
                    f = (f*10.0) + (*offset - '0');
                    ++offset;
                    ++n;
                }
                r += f / std::pow(10.0, n);
            }
            if (neg) {
                r = -r;
            }
            return r;
        }
    };

    template<>
    struct LexicalCast<int64_t>
    {
        static int64_t cast(const char* offset, size_t /*size*/)
        {
            int64_t x = 0;
            bool neg = false;
            if (*offset == '-') {
                neg = true;
                ++offset;
            }
            while (*offset >= '0' && *offset <= '9') {
                x = (x*10) + (*offset - '0');
                ++offset;
            }
            if (neg) {
                x = -x;
            }
            return x;
        }
    };

    template<>
    struct LexicalCast<bool>
    {
        static bool cast(const char* offset, size_t /*size*/)
        {
           return offset[0] == 'Y';
        }
    };

    template<>
    struct LexicalCast<FIX::UTCTimestamp>
    {
        static FIX::UTCTimestamp cast(const char* offset, size_t size)
        {
            if (size < 17) {
                throw std::runtime_error("Date/time string too short");
            }
            
            // Parse the first 18 characters: "YYYYMMDD-HH:mm:ss"
            std::tm tm = {};
            std::istringstream iss({offset, 17});
            iss >> std::get_time(&tm, "%Y%m%d-%H:%M:%S");
            if (iss.fail()) {
                throw std::runtime_error("Failed to parse date and time");
            }
            
            // Convert tm to time_t (local time) and then to time_point.
            std::time_t tt = std::mktime(&tm) - timezone;
            if(tt == -1)
                throw std::runtime_error("mktime failed");
            auto tp = std::chrono::system_clock::from_time_t(tt);

            // Now parse the fractional seconds, if any.
            std::chrono::microseconds ms(0);
            if (size > 17 && offset[17] == '.') { 
                int fraction_size = size - 18;
                // Optionally, limit to 3 digits for milliseconds.
                int fractional = {0};
                if (fraction_size > 3) {
                    auto [ptr, ec] = std::from_chars(offset + 18, offset + 18 + fraction_size, fractional);
                    if (ec != std::errc())
                        throw std::runtime_error("mktime failed");
                }
                // If the fractional part is not exactly 3 digits, adjust it:
                if (fraction_size== 1)
                    fractional *= 100000;   // "7" -> 700000 us
                else if (fraction_size== 2)
                    fractional *= 10000;    // "78" -> 780000 us
                 else if (fraction_size== 3)
                    fractional *= 1000;     // "123" -> 123000 us  
                ms = std::chrono::microseconds(fractional);
            }
            
            tp += ms;
            return tp;
        }
    };

    template<>
    struct LexicalCast<FIX::UTCDate>
    {
        static FIX::UTCDate cast(const char* offset, size_t size)
        {
            std::tm tm = {};
            std::istringstream ss({offset,size});
            
            // Parse the string into the tm structure
            ss >> std::get_time(&tm, "%Y-%m-%d");
            
            if (ss.fail()) {
                throw std::runtime_error("Failed to parse date string");
            }
            
            // Convert tm to time_t
            std::time_t time = std::mktime(&tm);
            
            if (time == -1) {
                throw std::runtime_error("Failed to convert tm to time_t");
            }
            
            return time;
        }
    };

    template<>
    struct LexicalCast<FIX::UTCTimeOnly>
    {
        static FIX::UTCTimeOnly cast(const char* offset, size_t size)
        {
            std::tm tm = {};
            std::istringstream ss({offset,size});
            
            // Parse the string into the tm structure
            ss >> std::get_time(&tm, "%H:%m:%s");
            
            if (ss.fail()) {
                throw std::runtime_error("Failed to parse date string");
            }
            
            // Convert tm to time_t
            std::time_t time = std::mktime(&tm);
            
            if (time == -1) {
                throw std::runtime_error("Failed to convert tm to time_t");
            }
            
            return time;
        }
    };
}


#endif //LEXICAL_CAST_HPP
#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <functional>

namespace qffixlib {

    enum class timestamp_format
    {
        seconds,
        milliseconds,
        microseconds
    };

    std::string timestamp_string(timestamp_format format);

    uint32_t number_of_digits(uint64_t value);

    uint32_t number_of_digits(int value);

    size_t modp_dtoa(double value, char* str, int prec);

}

#endif //UTILS_HPP
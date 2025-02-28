
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <memory>
#include "utils.hpp"

// other interesting references on num to string convesion
// http://www.jb.man.ac.uk/~slowe/cpp/itoa.html
// and http://www.ddj.com/dept/cpp/184401596?pgno=6

/**
 * Powers of 10
 * 10^0 to 10^9
 */

namespace qffixlib {

    static const double pow10_[] = {1, 10, 100, 1000, 10000, 100000, 1000000,
                                10000000, 100000000, 1000000000};

    static void strreverse(char* begin, char* end)
    {
        char aux;
        while (end > begin)
            aux = *end, *end-- = *begin, *begin++ = aux;
    }

    // slighly modified by DD to return target length
    size_t modp_dtoa(double value, char* str, int prec) // DD
    {
        /* if input is larger than thres_max, revert to exponential */
        const double thres_max = (double)(0x7FFFFFFF);

        double diff = 0.0;
        char* wstr = str;
        int neg = 0;
        int whole = 0;
        double tmp = 0.0;
        uint32_t frac = 0;

        /* Hacky test for NaN
        * under -fast-math this won't work, but then you also won't
        * have correct nan values anyways.  The alternative is
        * to link with libmath (bad) or hack IEEE double bits (bad)
        */
        if (! (value == value)) {
            str[0] = 'n'; str[1] = 'a'; str[2] = 'n'; str[3] = '\0';
            return 3; // DD
        }

        if (prec < 0) {
            prec = 0;
        } else if (prec > 9) {
            /* precision of >= 10 can lead to overflow errors */
            prec = 9;
        }


        /* we'll work in positive values and deal with the
        negative sign issue later */
        if (value < 0) {
            neg = 1;
            value = -value;
        }

        whole = (int) value;
        tmp = (value - whole) * pow10_[prec];
        frac = (uint32_t)(tmp);
        diff = tmp - frac;

        if (diff > 0.5) {
            ++frac;
            /* handle rollover, e.g.  case 0.99 with prec 1 is 1.0  */
            if (frac >= pow10_[prec]) {
                frac = 0;
                ++whole;
            }
        } else if (diff == 0.5 && ((frac == 0) || (frac & 1))) {
            /* if halfway, round up if odd, OR
            if last digit is 0.  That last part is strange */
            ++frac;
        }

        /* for very large numbers switch back to native sprintf for exponentials.
        anyone want to write code to replace this? */
        /*
        normal printf behavior is to print EVERY whole number digit
        which can be 100s of characters overflowing your buffers == bad
        */
        if (value > thres_max)
            return snprintf(str, 16, "%e", neg ? -value : value); // DD

        if (prec == 0) {
            diff = value - whole;
            if (diff > 0.5) {
                /* greater than 0.5, round up, e.g. 1.6 -> 2 */
                ++whole;
            } else if (diff == 0.5 && (whole & 1)) {
                /* exactly 0.5 and ODD, then round up */
                /* 1.5 -> 2, but 2.5 -> 2 */
                ++whole;
            }
        } else {    // these mods DD: remove trailing zero in prec (unless there is only one 0)
            int count = prec, done = 0;
            // now do fractional part, as an unsigned number
            do
            {
                --count;
                if (frac % 10)
                    done += (*wstr++ = (char)(48 + (frac % 10)));
                else if (done)
                    *wstr++ = '0';
            }
            while (frac /= 10);
            // add extra 0s
            if (!done)
                *wstr++ = '0';
            else
                while (count-- > 0)
                    *wstr++ = '0';
            // add decimal
            *wstr++ = '.';
        }

        // do whole part
        // Take care of sign
        // Conversion. Number is reversed.
        do
            *wstr++ = (char)(48 + (whole % 10));
        while (whole /= 10);
        if (neg)
            *wstr++ = '-';
        *wstr = 0;
        strreverse(str, wstr-1);
        return wstr - str; // DD
    }

    uint32_t number_of_digits(uint64_t value) 
    {
        return  1
            + (std::uint32_t)(value >= 10)
            + (std::uint32_t)(value >= 100)
            + (std::uint32_t)(value >= 1000)
            + (std::uint32_t)(value >= 10000)
            + (std::uint32_t)(value >= 100000)
            + (std::uint32_t)(value >= 1000000)
            + (std::uint32_t)(value >= 10000000)
            + (std::uint32_t)(value >= 100000000)
            + (std::uint32_t)(value >= 1000000000)
            + (std::uint32_t)(value >= 10000000000ull)
            + (std::uint32_t)(value >= 100000000000ull)
            + (std::uint32_t)(value >= 1000000000000ull)
            + (std::uint32_t)(value >= 10000000000000ull)
            + (std::uint32_t)(value >= 100000000000000ull)
            + (std::uint32_t)(value >= 1000000000000000ull)
            + (std::uint32_t)(value >= 10000000000000000ull)
            + (std::uint32_t)(value >= 100000000000000000ull)
            + (std::uint32_t)(value >= 1000000000000000000ull)
            + (std::uint32_t)(value >= 10000000000000000000ull);
    }

    uint32_t number_of_digits(int value)
    {
        return number_of_digits(static_cast<uint64_t>(std::abs(value)));
    }

}


#include "timer.hpp"

namespace qfapp {

    void Timer::reset() { 
    }

    void RecurringTimer::reset() { 
        auto now = std::chrono::steady_clock::now();
        mExpiry = now + mDuration;     
    }
}
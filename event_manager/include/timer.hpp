#ifndef TIMER_HPP
#define TIMER_HPP

#include <functional>
#include <chrono>
#include <string>

namespace qfapp {

    using TimerCallback = std::function<void()>;

    class Timer {
        public:
            Timer() = delete;

            virtual ~Timer() = default;

            Timer(TimerCallback callback, std::chrono::seconds duration, const std::string& timer_name)
                : mCallback(std::move(callback)),
                  mExpiry(std::chrono::steady_clock::now() + duration), 
                  mName(timer_name) {}

            virtual void reset();
            const std::string& name() { return mName;}
            const std::chrono::steady_clock::time_point& expiry() { return mExpiry;}
            bool elapsed(std::chrono::steady_clock::time_point& now) { return mExpiry <= now; }

            TimerCallback mCallback;
        protected:
            std::chrono::steady_clock::time_point mExpiry;
            std::string mName;
    };

    class RecurringTimer : public Timer {
        public:
            RecurringTimer() = delete;

            ~RecurringTimer() = default;

            RecurringTimer(std::chrono::seconds duration, TimerCallback callback, const std::string& timer_name)
                : Timer(callback, duration, timer_name),  mDuration(duration) {}

            void reset() override;
        private:
            std::chrono::seconds mDuration;
    };

}

#endif // TIMER_HPP

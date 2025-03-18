#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <string>
#include "logger.hpp"
#include "app_options.hpp"
#include "logger_options.hpp"
#include "event_manager.hpp"
#include "event_manager_interface.hpp"

namespace qfapp {

    class Application {
    public:
        Application(AppOptions options, LoggerOptions loggerOptions, const spdlog::pattern_time_type);

        Application(const Application &) = delete;
        Application(Application &&) = delete;
        Application &operator=(const Application &) = delete;
        Application &operator=(Application &&) = delete;
        virtual ~Application() = default;

        virtual void setup() {}
        virtual void start() {}
        virtual void run();


    protected:

        Logger mLogger;
        AppOptions mAppOptions;
        std::shared_ptr<EventManager> mEventManager;
    };

}

#endif

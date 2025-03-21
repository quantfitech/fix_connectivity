#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <string>
#include "logger.hpp"
#include "app_options.hpp"
#include "logger_options.hpp"
#include "event_manager.hpp"
#include "event_manager_interface.hpp"

namespace qfapp {

    #define SENDER_COMP_ID "SENDER_COMP_ID"
    #define TARGET_COMP_ID "TARGET_COMP_ID"
    #define SESSION_PASSWORD "SESSION_PASSWORD"
    #define SESSION_SECRET "SESSION_SECRET"
    #define SERVER_IP "SERVER_IP"
    #define SERVER_PORT "SERVER_PORT"

    #define REDIS_IP "REDIS_IP"
    #define REDIS_PORT "REDIS_PORT" 

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

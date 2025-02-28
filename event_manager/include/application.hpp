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
        Application(AppOptions options, LoggerOptions loggerOptions);

        Application(const Application &) = delete;
        Application(Application &&) = delete;
        Application &operator=(const Application &) = delete;
        Application &operator=(Application &&) = delete;
        virtual ~Application() = default;

        void add_timer(std::chrono::milliseconds, TimerCallback);
        void add_file_descriptor(FileDescriptor*, RW_FLAG); 

        void start();
        virtual void run();


    private:

        Logger mLogger;
        AppOptions mAppOptions;
        EventManager mEventManager;
    };

}

#endif

#include "application.hpp"
#include "logger_options.hpp"
#include "logger.hpp"



namespace qfapp {

    Application::Application(AppOptions app_options, LoggerOptions loggerOptions, const spdlog::pattern_time_type time_pattern): 
        mLogger(loggerOptions, app_options.application_name, time_pattern), mAppOptions(app_options) 
        { 
            mEventManager = std::make_shared<EventManager>();
        }

    void Application::run() {
        setup();
        start();
        LOG_INFO("run application {}", mAppOptions.application_name);
        mEventManager->run();
    }


}
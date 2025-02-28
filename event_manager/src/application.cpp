#include "application.hpp"
#include "logger_options.hpp"
#include "logger.hpp"



namespace qfapp {

Application::Application(AppOptions app_options, LoggerOptions loggerOptions): mLogger(loggerOptions, app_options.application_name), mAppOptions(app_options) { 
}

void Application::start(){

}

void Application::add_timer(std::chrono::milliseconds , TimerCallback ) {
    //LOG_INFO(" adding timer: duration {}", std::to_string(duration.count()));
    //mEventManager.addTimer(duration, callback);
}
void Application::add_file_descriptor(FileDescriptor* fileDescriptor, RW_FLAG flag) {
    //LOG_INFO(" adding fd {}", fileDescriptor.get()->getFd());
    mEventManager.addFileDescriptor(fileDescriptor, flag);
}


void Application::run() {

}


}
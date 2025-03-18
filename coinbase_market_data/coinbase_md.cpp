#include "coinbase_md_app.hpp"
#include <cstdlib>
#include <string.h>

using namespace qfapp;
using namespace coinbase_md;
using namespace qffixlib;

#define CONSOLE_LOG_FLAG "CONSOLE_LOG_FLAG"
#define LOG_LEVEL "LOG_LEVEL"
#define LOG_TIME_FORMAT "LOG_TIME_FORMAT"


int main() {

    AppOptions app_options;
    app_options.application_name = "coinbase_md";
    LoggerOptions logging_options;
    auto console_log = std::getenv(CONSOLE_LOG_FLAG);
    if (std::strcmp(console_log, "1") == 0 ||  std::strcmp(console_log, "ON") == 0 || std::strcmp(console_log, "Y") == 0) {
        logging_options.console_log = true;
    }
    auto log_level = std::getenv(LOG_LEVEL);
    logging_options.console_log_level_str = log_level;

    auto log_time_format = std::getenv(LOG_TIME_FORMAT);
    spdlog::pattern_time_type time_format = spdlog::pattern_time_type::local;
    if (std::strcmp(log_time_format, "UTC") == 0) {
        time_format = spdlog::pattern_time_type::utc;
    }

    std::signal(SIGINT, CoinbaseMDApp::signalHandler);
    std::signal(SIGTERM, CoinbaseMDApp::signalHandler); 

    auto app = std::make_unique<CoinbaseMDApp>(app_options, logging_options, time_format); 
    LOG_INFO("starting app");
    app->run();

    return 0;
}


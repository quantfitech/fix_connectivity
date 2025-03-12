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

    setenv(SERVER_IP, "3.114.19.227", 1);
    setenv("SERVER_PORT", "6120", 1);
    setenv(CONSOLE_LOG_FLAG, "Y", 1);
    setenv(LOG_TIME_FORMAT, "UTC", 1);
    setenv("LOG_LEVEL", "debug", 1);

    //setenv("SENDER_COMP_ID", "pv3hnDiPUkJrGS5K", 1);
    //setenv("TARGET_COMP_ID", "CBINTLMD", 1);
    //setenv("SESSION_PASSWORD", "jhgJHGJHFGHf765jhgffghg", 1);
    //setenv("SESSION_SECRET", "QzAxdm1lUEZFWWoxSlZlNVNRNFpCOENUQ0pEbGZabkI3NE5yTlhjUUg4SkJsZGltN3pBbFg3SElRSzFlYUt4WQ==", 1);
    setenv("SENDER_COMP_ID", "pmRxEAa4bln68mhX", 1);
    setenv("TARGET_COMP_ID", "CBINTLMD", 1);
    setenv("SESSION_PASSWORD", "JHG7887hjgjh786tgNJGFU^", 1);
    setenv("SESSION_SECRET", "Wng4RjN3T0pEZHp6MXZNbzZYN1IwTDlnUlNIUGRhRW81Y0pkeEhsTXNaTjllOVYxU3JHOGkxZVk3OUNDaWNYQw==", 1);

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


#include "logger.hpp"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

using namespace qfapp;

Logger::Logger(const LoggerOptions &options, const std::string &app_name)
{
  Init(options, app_name);
}

void Logger::Init(const LoggerOptions &options, const std::string &app_name)
{
  if (options.rotating_logger) {
    auto error_logger{std::make_shared<spdlog::sinks::daily_file_sink_mt>(options.error_log_filename, 0, 0)};
    error_logger->set_level(options.error_level);
    m_sinks.push_back(error_logger);

    const auto info_logger{std::make_shared<spdlog::sinks::daily_file_sink_mt>(options.base_log_filename, 0, 0)};
    info_logger->set_level(options.base_level);
    m_sinks.push_back(info_logger);
  } else {
    const auto error_logger{std::make_shared<spdlog::sinks::basic_file_sink_mt>(options.error_log_filename)};
    error_logger->set_level(options.error_level);
    m_sinks.push_back(error_logger);

    const auto info_logger{std::make_shared<spdlog::sinks::basic_file_sink_mt>(options.base_log_filename)};
    info_logger->set_level(options.base_level);
    m_sinks.push_back(info_logger);
  }

  auto console_level{spdlog::level::info};

  if (options.console_log) {
    if (options.console_log_level_str == "info")
      console_level = spdlog::level::info;
    else if (options.console_log_level_str == "debug")
      console_level = spdlog::level::debug;
    else if (options.console_log_level_str == "warn")
      console_level = spdlog::level::warn;
    else if (options.console_log_level_str == "err" || options.console_log_level_str == "error")
      console_level = spdlog::level::err;
    else if (options.console_log_level_str == "trace")
      console_level = spdlog::level::trace;

    const auto console_logger{std::make_shared<spdlog::sinks::stdout_color_sink_mt>()};

    console_logger->set_level(console_level);
    m_sinks.push_back(console_logger);
  }

  m_combined_logger = std::make_shared<spdlog::logger>(app_name, begin(m_sinks), end(m_sinks));

  m_combined_logger->set_level(std::min(console_level, options.base_level));

  // set log pattern in UTC:
  // [date,time][thread id=%t][logger name=%n][short loglevel=%L][sourcefile:line=%s:%#] log line=%v
  m_combined_logger->set_pattern("[%Y-%m-%dT%H:%M:%S.%FZ][%t][%n][%^%L%$][%s:%#] %v", spdlog::pattern_time_type::utc);

  spdlog::set_default_logger(m_combined_logger);
  m_combined_logger->flush_on(options.base_level);
  
}

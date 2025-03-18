#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "logger_options.hpp"
#include <memory>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>

namespace qfapp {

    class Logger {
    public:
        Logger(const Logger &) = delete;
        Logger(Logger &&) = delete;
        Logger &operator=(const Logger &) = delete;
        Logger &operator=(Logger &&) = delete;

        explicit Logger(const LoggerOptions &options, const std::string &app_name, const spdlog::pattern_time_type);
        void Init(const LoggerOptions &options, const std::string &app_name, const spdlog::pattern_time_type);

    private:
        LoggerOptions m_options;
        std::vector<spdlog::sink_ptr> m_sinks;
        std::shared_ptr<spdlog::logger> m_combined_logger;
    };

}   // namespace quantfiapp

#define LOG_TRACE(...) SPDLOG_LOGGER_CALL(spdlog::default_logger(), spdlog::level::trace, __VA_ARGS__);
#define LOG_DEBUG(...) SPDLOG_LOGGER_CALL(spdlog::default_logger(), spdlog::level::debug, __VA_ARGS__);
#define LOG_INFO(...) SPDLOG_LOGGER_CALL(spdlog::default_logger(), spdlog::level::info, __VA_ARGS__);
#define LOG_WARN(...) SPDLOG_LOGGER_CALL(spdlog::default_logger(), spdlog::level::warn, __VA_ARGS__);
#define LOG_ERROR(...) SPDLOG_LOGGER_CALL(spdlog::default_logger(), spdlog::level::err, __VA_ARGS__);
#define LOG_CRITICAL(...) SPDLOG_LOGGER_CALL(spdlog::default_logger(), spdlog::level::critical, __VA_ARGS__);

#endif   // LOGGER_HPP
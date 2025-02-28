#ifndef LOGGER_OPTIONS_HPP
#define LOGGER_OPTIONS_HPP

#include <spdlog/spdlog.h>
#include <string>

namespace qfapp {

struct LoggerOptions {
  bool console_log{};
  std::string base_log_filename{};
  std::string error_log_filename{};
  bool rotating_logger{true};
  spdlog::level::level_enum error_level{spdlog::level::err};
  spdlog::level::level_enum base_level{spdlog::level::info};
  spdlog::level::level_enum console_level{spdlog::level::info};
  std::string console_log_level_str{};
};

}   // namespace tickdata

#endif   // LOGGER_OPTIONS_HPP
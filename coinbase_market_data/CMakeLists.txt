
if (APPLE)
    include_directories(/opt/homebrew/include)
endif()

find_package(OpenSSL REQUIRED)
find_package(spdlog REQUIRED)

add_executable(coinbase_md coinbase_md_session.cpp coinbase_md.cpp)
if (APPLE)
    target_link_libraries(coinbase_md PRIVATE spdlog::spdlog_header_only fixlib OpenSSL::SSL event_manager)
elseif(UNIX AND NOT APPLE)    
    target_link_libraries(coinbase_md PRIVATE spdlog::spdlog_header_only fixlib OpenSSL::SSL event_manager)
endif()
target_include_directories(coinbase_md PRIVATE ../fix_lib/include ../fix_lib/versions)

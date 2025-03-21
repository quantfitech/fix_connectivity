
if (APPLE)
    include_directories(/opt/homebrew/include)
    set(HIREDIS_INCLUDE_DIR "/opt/homebrew/opt/hiredis/include")
    set(HIREDIS_LIBRARY "/opt/homebrew/opt/hiredis/lib/libhiredis.dylib")
elseif(UNIX AND NOT APPLE)
    set(HIREDIS_INCLUDE_DIR "/hiredis/")
    set(HIREDIS_LIBRARY "/hiredis/build/libhiredis.so")  
endif()

find_package(OpenSSL REQUIRED)
find_package(spdlog REQUIRED)

add_executable(coinbase_md coinbase_md_session.cpp coinbase_md.cpp)
target_link_libraries(coinbase_md PRIVATE spdlog::spdlog_header_only fixlib OpenSSL::SSL event_manager redis_cpp ${HIREDIS_LIBRARY})
target_include_directories(coinbase_md PRIVATE ../fix_lib/include ../fix_lib/versions ${HIREDIS_INCLUDE_DIR} ../redis)

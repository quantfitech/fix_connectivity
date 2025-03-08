if (APPLE)
    include_directories(/opt/homebrew/include)
    # Manually specify hiredis paths
    set(HIREDIS_INCLUDE_DIR "/opt/homebrew/opt/hiredis/include")
    set(HIREDIS_LIBRARY "/opt/homebrew/opt/hiredis/lib/libhiredis.dylib")
elseif(UNIX AND NOT APPLE)
    set(HIREDIS_INCLUDE_DIR "/hiredis/")
    set(HIREDIS_LIBRARY "/hiredis/build/libhiredis.so")  
endif()

find_package(spdlog REQUIRED)

add_executable(redis_cpp redis_example.cpp)
if (APPLE)
    target_link_libraries(redis_cpp PRIVATE spdlog::spdlog_header_only event_manager ${HIREDIS_LIBRARY})
elseif(UNIX AND NOT APPLE)    
    target_link_libraries(redis_cpp PRIVATE spdlog::spdlog_header_only event_manager ${HIREDIS_LIBRARY})
endif()
target_include_directories(redis_cpp PRIVATE ${HIREDIS_INCLUDE_DIR} ../event_manager/include)

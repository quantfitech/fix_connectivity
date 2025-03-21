
# Set the library name
set(LIB_NAME redis_cpp)


# Define the sources for the static library
set(LIB_SOURCES
    src/redis_endpoint.cpp
)

# Define the headers for the static library
set(LIB_HEADERS
    include
)

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

#add_executable(redis_cpp redis_example.cpp)   
#target_link_libraries(redis_cpp PRIVATE spdlog::spdlog_header_only event_manager ${HIREDIS_LIBRARY})
#target_include_directories(redis_cpp PRIVATE ${HIREDIS_INCLUDE_DIR} ../event_manager/include)

# Add the static library target
add_library(${LIB_NAME} STATIC ${LIB_SOURCES})

# Specify include directories for consumers of the library
target_include_directories(${LIB_NAME} PUBLIC ${LIB_HEADERS} lib/include ../event_manager/include)

# Optional: Add compile options or flags
#target_compile_options(${LIB_NAME}  PRIVATE -Wall -Wextra -Werror)
target_compile_options(${LIB_NAME}  PRIVATE -Wall -Wextra)

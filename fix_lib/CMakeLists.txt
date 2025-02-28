set(LIB_NAME fixlib)

# Add the library source files
set(LIB_SOURCES
    src/session.cpp
    src/client_connection.cpp
    src/session_state.cpp
    src/reader_buffer.cpp
    src/base64_hmac.cpp
    src/tcp_socket.cpp
    src/ssl_socket.cpp
    src/utils.cpp
    src/token_iterator.cpp
)

# Add the library include directory
set(LIB_INCLUDES
    include versions
)

if (APPLE)
    include_directories(/opt/homebrew/opt/tinyxml2/include)
    include_directories(/opt/homebrew/include)
endif()

# Create a static library target
add_library(${LIB_NAME} STATIC ${LIB_SOURCES})

# Include the library's headers
target_include_directories(${LIB_NAME} PUBLIC ${LIB_INCLUDES} ../event_manager/include)

# Optional: Add compile options or flags
target_compile_options(${LIB_NAME} PRIVATE -Wall -Wextra -Werror)

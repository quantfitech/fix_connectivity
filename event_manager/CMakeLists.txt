# Set the library name
set(LIB_NAME event_manager)

# Define the sources for the static library
set(LIB_SOURCES
    src/event_manager.cpp
    src/logger.cpp
    src/timer.cpp
    src/application.cpp
)

# Define the headers for the static library
set(LIB_HEADERS
    include
)

if (APPLE)
    include_directories(/opt/homebrew/include)
endif()

# Add the static library target
add_library(${LIB_NAME} STATIC ${LIB_SOURCES})

# Specify include directories for consumers of the library
target_include_directories(${LIB_NAME} PUBLIC ${LIB_HEADERS})

# Optional: Add compile options or flags
#target_compile_options(${LIB_NAME}  PRIVATE -Wall -Wextra -Werror)
target_compile_options(${LIB_NAME}  PRIVATE -Wall -Wextra)
cmake_minimum_required(VERSION 3.10)
project(FixProtocolLib)
include (CheckCXXCompilerFlag)

CHECK_CXX_COMPILER_FLAG("-std=c++20" COMPILER_SUPPORTS_CXX20)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)

if (COMPILER_SUPPORTS_CXX20)
    message(STATUS "Enabling C++20 mode")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
elseif (COMPILER_SUPPORTS_CXX20)
    message(STATUS "Enabling C++14 mode")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support. Please use a different C++ compiler.")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(spdlog REQUIRED)

# Add the event_manager library
add_subdirectory(fix_lib)

# Add the example application
add_subdirectory(example)

# Add the example application
add_subdirectory(event_manager)

# Add the example application
add_subdirectory(coinbase_market_data)


#enable_testing()
add_subdirectory(tests)

add_subdirectory(redis)
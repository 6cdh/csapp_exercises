cmake_minimum_required(VERSION 3.17)
project(csapp_exercises)

# ISO C11
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# ISO C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# export compile database
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#
# Source definitions
#

include_directories(include)

set(SRC_LIB exercises)

add_subdirectory(src)

#
# Test definitions
#

enable_testing()

add_subdirectory(test)

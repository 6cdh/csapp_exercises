cmake_minimum_required (VERSION 3.8)
project (sample)

set(WALL_FLAGS "-Wall -Wextra -Wno-long-long -Wno-variadic-macros -Wshadow -Wno-error=dangling-else")
set(FLAGS_DEBUG "${WALL_FLAGS} -fexceptions")
set(FLAGS_RELEASE "${WALL_FLAGS} -march=native -O2 -pipe -fomit-frame-pointer -DNDEBUG")

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED true)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_C_EXTENSIONS off)
set(CMAKE_CXX_EXTENSIONS off)

set(CMAKE_C_FLAGS_DEBUG ${FLAGS_DEBUG})
set(CMAKE_C_FLAGS_RELEASE ${FLAGS_RELEASE})
set(CMAKE_CXX_FLAGS_DEBUG ${FLAGS_DEBUG})
set(CMAKE_CXX_FLAGS_RELEASE ${FLAGS_RELEASE})

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS_RELEASE})
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS_RELEASE})

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

#
# Source definitions
#

set(SRC_DIR src)
set(BIN_DIR ${CMAKE_BINARY_DIR})
set(LIB_DIR ${CMAKE_BINARY_DIR}/lib)
set(SRC_LIB chapters)

include_directories("${CMAKE_SOURCE_DIR}/include")
link_directories(${LIB_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB_DIR})

add_subdirectory(${SRC_DIR})

#
# Test definitions
#

set(TEST_DIR test)
include(cmake/googletest.cmake)
add_subdirectory(${TEST_DIR})

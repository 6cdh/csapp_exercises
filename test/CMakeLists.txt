# GoogleTest
include(FetchContent)

FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        703bd9caab50b139428cea1aaff9974ebee5742e # 1.10.0
    )

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

# test

aux_source_directory(. SRCS)

set(TEST_EXE csapp_test)
add_executable(${TEST_EXE} ${SRCS})

target_link_libraries(${TEST_EXE} PRIVATE gtest ${SRC_LIB})

add_test(NAME ${TEST_EXE} COMMAND ${TEST_EXE})

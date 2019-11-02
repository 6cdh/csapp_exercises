aux_source_directory(. TEST_SRCS)

set(TEST_EXE tests)

# Now simply link against gtest or gtest_main as needed. Eg

add_executable(${TEST_EXE} ${TEST_SRCS})
target_link_libraries(${TEST_EXE} gtest_main ${SRC_LIB})
add_test(NAME ${TEST_EXE} COMMAND ${TEST_EXE})

enable_testing()
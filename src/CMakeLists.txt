set(EXE_NAME target)

add_custom_target(run
        COMMAND ${EXE_NAME}
        DEPENDS ${EXE_NAME}
        WORKING_DIRECTORY ${BIN_DIR}
        )

add_subdirectory(Chapters)
add_executable(${EXE_NAME} main.c)
target_link_libraries(${EXE_NAME} PUBLIC ${SRC_LIB})
target_include_directories(${EXE_NAME} PUBLIC ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/${SRC_DIR}/Chapters)
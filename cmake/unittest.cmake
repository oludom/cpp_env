add_subdirectory(${CMAKE_SOURCE_DIR}/test)

set(CHECK_ARGS COMMAND echo 0 > n_failed.txt)

foreach(TEST ${TESTS})
    add_executable(${TEST} ${CMAKE_SOURCE_DIR}/test/${${TEST}_SRC} ${CMAKE_SOURCE_DIR}/3rdparty/uunit/uunit.cc)
    target_include_directories(${TEST} PUBLIC ${CMAKE_SOURCE_DIR}/3rdparty/uunit)
    target_compile_definitions(${TEST} PUBLIC OUTPUT="${TEST}")
    list(APPEND CHECK_ARGS
        COMMAND echo -n "${TEST}: "
        COMMAND ${TEST} 2> ${TEST}.log || (expr `cat n_failed.txt` + 1 > n_failed.txt)
        COMMAND echo)
endforeach()

add_custom_target(check
    DEPENDS ${TESTS}
    ${CHECK_ARGS}
    COMMAND echo "-----"
    COMMAND echo "Failed tests: " `cat n_failed.txt`
    COMMAND echo "-----"
)
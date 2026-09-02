include(GoogleTest)

function(add_gtest LIB_NAME TEST_NAME)
    set(TARGET_NAME chassis_${LIB_NAME}_test_${TEST_NAME})
    add_executable(${TARGET_NAME})
    target_sources(${TARGET_NAME} PRIVATE ${TEST_NAME}.test.cpp)
    target_link_libraries(
        ${TARGET_NAME}
        PRIVATE
            chassis::${LIB_NAME}
            beman::expected
            GTest::gtest_main
    )
    gtest_discover_tests(${TARGET_NAME})
endfunction()

add_subdirectory(core)
add_subdirectory(filesystem)
add_subdirectory(manifest)
add_subdirectory(application)

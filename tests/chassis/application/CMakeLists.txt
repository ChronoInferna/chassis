add_gtest(application use_cases)

add_executable(chassis_cli_test_wiring cli_wiring.test.cpp)
target_link_libraries(
    chassis_cli_test_wiring
    PRIVATE
        chassis_cli_commands
        GTest::gtest_main
)
gtest_discover_tests(chassis_cli_test_wiring)

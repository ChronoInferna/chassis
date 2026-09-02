add_executable(chassis_application_test_use_cases use_cases.test.cpp)
target_link_libraries(
    chassis_application_test_use_cases
    PRIVATE
        chassis::application
        GTest::gtest_main
)
gtest_discover_tests(chassis_application_test_use_cases)

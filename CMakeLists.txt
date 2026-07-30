cmake_minimum_required(VERSION 3.28)

project(
    chassis
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(CHASSIS_BUILD_TESTS "Build tests" ON)

add_subdirectory(libs)

if(CHASSIS_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests/chassis)
endif()

# add_subdirectory(apps)

# install(
#     EXPORT chassisTargets
#     NAMESPACE chassis::
# )

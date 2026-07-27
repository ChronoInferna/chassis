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

# TODO Move to apps/chassis?
include(FetchContent)

FetchContent_Declare(
    CLI11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG v2.6.2
)

FetchContent_MakeAvailable(CLI11)
# target_link_libraries(chassis PRIVATE CLI11::CLI11)

add_subdirectory(libs/core)
add_subdirectory(libs/filesystem)
add_subdirectory(libs/manifest)

if(CHASSIS_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests/chassis)
endif()

# add_subdirectory(apps/chassis)

# install(
#     EXPORT chassisTargets
#     NAMESPACE chassis::
# )

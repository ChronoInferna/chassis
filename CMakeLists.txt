cmake_minimum_required(VERSION 3.28)

project(
    chassis
    VERSION 0.1.0
    LANGUAGES CXX
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(FetchContent)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#
# Options
#

option(CHASSIS_BUILD_TESTS "Build tests" ON)

#
# Dependencies
#

# beman.expected for expected over reference support
FetchContent_Declare(
    beman.expected
    GIT_REPOSITORY https://github.com/bemanproject/expected.git
    GIT_TAG main
    FIND_PACKAGE_ARGS CONFIG
)

FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG v3.4.0
    FIND_PACKAGE_ARGS CONFIG
)

FetchContent_MakeAvailable(beman.expected tomlplusplus)

if(CHASSIS_BUILD_TESTS)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
        FIND_PACKAGE_ARGS CONFIG
    )

    FetchContent_MakeAvailable(googletest)
endif()

#
# Build
#

add_subdirectory(libs)
add_subdirectory(apps)

if(CHASSIS_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests/chassis)
endif()

#
# Package
#

configure_package_config_file(
    cmake/chassisConfig.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/chassisConfig.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/chassis"
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/chassisConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/chassisConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/chassisConfigVersion.cmake"
    DESTINATION
        "${CMAKE_INSTALL_LIBDIR}/cmake/chassis"
)

install(
    EXPORT chassisTargets
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/chassis"
    NAMESPACE chassis::
    FILE chassisTargets.cmake
)

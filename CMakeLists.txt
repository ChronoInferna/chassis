cmake_minimum_required(VERSION 3.28)

project(
    chassis
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(CHASSIS_BUILD_TESTS "Build tests" ON)

add_subdirectory(libs)
add_subdirectory(apps)

if(CHASSIS_BUILD_TESTS)
    add_subdirectory(tests/chassis)
    enable_testing()
endif()

include(GNUInstallDirs)
install(
    EXPORT chassisTargets
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/chassis"
    NAMESPACE chassis::
    FILE chassis-config.cmake
)

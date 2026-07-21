cmake_minimum_required(VERSION 3.28)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

project(
    title # TODO
    DESCRIPTION
        "" # TODO
    LANGUAGES CXX
    VERSION 0.1.0
)

# Tests
option(
    title_BUILD_TESTS # TODO
    "Enable building tests and test infrastructure. Default: ${PROJECT_IS_TOP_LEVEL}. Values: { ON, OFF }."
    ${PROJECT_IS_TOP_LEVEL}
)

# Examples
option(
    title_BUILD_EXAMPLES # TODO
    "Enable building examples. Default: ${PROJECT_IS_TOP_LEVEL}. Values: { ON, OFF }."
    ${PROJECT_IS_TOP_LEVEL}
)

add_library(title INTERFACE) # TODO
add_library(title::title ALIAS title) # TODO

target_sources(
    title # TODO
    PUBLIC
        FILE_SET HEADERS
            BASE_DIRS
                "${CMAKE_CURRENT_SOURCE_DIR}/include"
                "${CMAKE_CURRENT_BINARY_DIR}/include"
)

set_target_properties(
    title # TODO
    PROPERTIES VERIFY_INTERFACE_HEADER_SETS ${PROJECT_IS_TOP_LEVEL}
)

add_subdirectory(include/title) # TODO

# Install the library
install(
    TARGETS title # TODO
    EXPORT titleTargets # TODO
    FILE_SET HEADERS
)

# Generate import target
install(
    EXPORT titleTargets # TODO
    FILE titleTargets.cmake # TODO
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/title # TODO
    NAMESPACE title:: # TODO
)

# Generate config files
configure_package_config_file(
    "cmake/titleConfig.cmake.in" # TODO
    "${CMAKE_CURRENT_BINARY_DIR}/titleConfig.cmake" # TODO
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/title # TODO
)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/titleConfigVersion.cmake" # TODO
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)
install(
    FILES
    "${CMAKE_CURRENT_BINARY_DIR}/titleConfig.cmake" # TODO
    "${CMAKE_CURRENT_BINARY_DIR}/titleConfigVersion.cmake" # TODO
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/title # TODO
)

if(title_BUILD_TESTS) # TODO
    enable_testing()
    # add_subdirectory(tests/title) # TODO
endif()

if(title_BUILD_EXAMPLES) # TODO
    add_subdirectory(examples)
endif()

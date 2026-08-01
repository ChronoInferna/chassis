# beman.expected for expected over reference support
include(FetchContent)

FetchContent_Declare(
    beman.expected
    GIT_REPOSITORY https://github.com/bemanproject/expected.git
    GIT_TAG main
)
FetchContent_MakeAvailable(beman.expected)

add_library(chassis_core)
add_library(chassis::core ALIAS chassis_core)

target_sources(chassis_core
    PRIVATE
        src/error/error.cpp

    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include"
        FILES
            include/chassis/core/error/error.hpp
)

target_link_libraries(chassis_core
    PUBLIC
        beman::expected
)

target_compile_features(chassis_core PUBLIC cxx_std_23)

set_target_properties(
    chassis_core
    PROPERTIES VERIFY_INTERFACE_HEADER_SETS ${PROJECT_IS_TOP_LEVEL}
)

# Install the library
install(
    TARGETS chassis_core
    EXPORT chassisTargets
    FILE_SET HEADERS
)

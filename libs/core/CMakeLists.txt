add_library(chassis_core)
add_library(chassis::core ALIAS chassis_core)

target_sources(chassis_core
    PRIVATE
        src/error.cpp

    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include"
        FILES
            include/chassis/core/error/error.hpp
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

if(CHASSIS_BUILD_TESTS)
    # add_subdirectory(tests/chassis_core) # TODO
endif()

add_library(chassis_process STATIC)
add_library(chassis::process ALIAS chassis_process)

target_sources(chassis_process
    PRIVATE
        src/chassis/process/process.cpp

    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include"
        FILES
            include/chassis/process/process.hpp
)

target_link_libraries(chassis_process
    PUBLIC
        chassis::core
        chassis::filesystem
)

target_compile_features(chassis_process PUBLIC cxx_std_23)

set_target_properties(
    chassis_process
    PROPERTIES VERIFY_INTERFACE_HEADER_SETS ${PROJECT_IS_TOP_LEVEL}
)

# Install the library
install(
    TARGETS chassis_process
    EXPORT chassisTargets
    FILE_SET HEADERS
)

add_library(chassis_builder STATIC)
add_library(chassis::builder ALIAS chassis_builder)

target_sources(chassis_builder
    PRIVATE
        src/chassis/builder/cmake_builder.cpp

    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include"
        FILES
            include/chassis/builder/builder.hpp
            include/chassis/builder/cmake_builder.hpp
)

target_link_libraries(chassis_builder
    PUBLIC
        chassis::core
        chassis::filesystem
        chassis::manifest
        chassis::process
)

target_compile_features(chassis_builder PUBLIC cxx_std_23)

set_target_properties(
    chassis_builder
    PROPERTIES VERIFY_INTERFACE_HEADER_SETS ${PROJECT_IS_TOP_LEVEL}
)

# Install the library
install(
    TARGETS chassis_builder
    EXPORT chassisTargets
    FILE_SET HEADERS
)

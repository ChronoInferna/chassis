add_library(chassis_manifest STATIC)
add_library(chassis::manifest ALIAS chassis_manifest)

target_sources(chassis_manifest
    PRIVATE
        src/chassis/manifest/manifest.cpp

    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include"
        FILES
            include/chassis/manifest/manifest.hpp
)

target_link_libraries(chassis_manifest
    PUBLIC
        chassis::core
        chassis::filesystem
    PRIVATE
        $<BUILD_INTERFACE:tomlplusplus::tomlplusplus> # TODO used here because of FetchContent problems - hopefully can be resolved as I figure out best practices
)

target_compile_features(chassis_manifest PUBLIC cxx_std_23)

set_target_properties(
    chassis_manifest
    PROPERTIES VERIFY_INTERFACE_HEADER_SETS ${PROJECT_IS_TOP_LEVEL}
)

# Install the library
install(
    TARGETS chassis_manifest
    EXPORT chassisTargets
    FILE_SET HEADERS
)

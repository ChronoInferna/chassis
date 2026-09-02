add_library(chassis_infrastructure STATIC)
add_library(chassis::infrastructure ALIAS chassis_infrastructure)

target_sources(chassis_infrastructure
    PRIVATE
        src/chassis/infrastructure/manifest/toml_manifest_store.cpp
        src/chassis/infrastructure/process/posix_process_runner.cpp
        src/chassis/infrastructure/project/basic_project_generator.cpp

    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include"
        FILES
            include/chassis/infrastructure/manifest/toml_manifest_store.hpp
            include/chassis/infrastructure/process/posix_process_runner.hpp
            include/chassis/infrastructure/project/basic_project_generator.hpp
)

target_link_libraries(chassis_infrastructure
    PUBLIC
        chassis::application
        chassis::filesystem
        chassis::manifest
        chassis::process
)

target_compile_features(chassis_infrastructure PUBLIC cxx_std_23)

set_target_properties(
    chassis_infrastructure
    PROPERTIES VERIFY_INTERFACE_HEADER_SETS ${PROJECT_IS_TOP_LEVEL}
)

install(
    TARGETS chassis_infrastructure
    EXPORT chassisTargets
    FILE_SET HEADERS
)

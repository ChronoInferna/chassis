add_library(chassis_application STATIC)
add_library(chassis::application ALIAS chassis_application)

target_sources(chassis_application
    PRIVATE
        src/chassis/application/use_cases/init_project_use_case.cpp
        src/chassis/application/use_cases/new_project_use_case.cpp
        src/chassis/application/use_cases/build_project_use_case.cpp

    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include"
        FILES
            include/chassis/application/command_result.hpp
            include/chassis/application/ports/manifest_store.hpp
            include/chassis/application/ports/process_runner.hpp
            include/chassis/application/ports/project_generator.hpp
            include/chassis/application/use_cases/init_project_use_case.hpp
            include/chassis/application/use_cases/new_project_use_case.hpp
            include/chassis/application/use_cases/build_project_use_case.hpp
)

target_link_libraries(chassis_application
    PUBLIC
        chassis::core
        chassis::filesystem
        chassis::manifest
        chassis::domain
)

target_compile_features(chassis_application PUBLIC cxx_std_23)

set_target_properties(
    chassis_application
    PROPERTIES VERIFY_INTERFACE_HEADER_SETS ${PROJECT_IS_TOP_LEVEL}
)

install(
    TARGETS chassis_application
    EXPORT chassisTargets
    FILE_SET HEADERS
)

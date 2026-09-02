add_library(chassis_domain STATIC)
add_library(chassis::domain ALIAS chassis_domain)

target_sources(chassis_domain
    PRIVATE
        src/chassis/domain/project/project_rules.cpp

    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include"
        FILES
            include/chassis/domain/project/project_rules.hpp
)

target_link_libraries(chassis_domain
    PUBLIC
        chassis::core
        chassis::filesystem
)

target_compile_features(chassis_domain PUBLIC cxx_std_23)

set_target_properties(
    chassis_domain
    PROPERTIES VERIFY_INTERFACE_HEADER_SETS ${PROJECT_IS_TOP_LEVEL}
)

install(
    TARGETS chassis_domain
    EXPORT chassisTargets
    FILE_SET HEADERS
)

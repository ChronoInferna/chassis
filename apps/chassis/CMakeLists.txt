include(FetchContent)

FetchContent_Declare(
    CLI11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG v2.6.2
)
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.17.0
)

FetchContent_MakeAvailable(CLI11 spdlog)

#
# Application Layer Library (Services & Use Cases)
#

add_library(chassis_app STATIC)
add_library(chassis::app ALIAS chassis_app)

target_sources(chassis_app
    PRIVATE
        src/application/project_service.cpp
        src/application/init_service.cpp
        src/application/build_service.cpp
        src/application/run_service.cpp

    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/src"
        FILES
            src/application/project_service.hpp
            src/application/init_service.hpp
            src/application/build_service.hpp
            src/application/run_service.hpp
)

target_link_libraries(chassis_app
    PUBLIC
        chassis::core
        chassis::filesystem
        chassis::manifest
        chassis::process
        chassis::builder
)

target_compile_features(chassis_app PUBLIC cxx_std_23)

#
# Infrastructure Layer & Binary
#

add_executable(chassis_cli)
set_target_properties(chassis_cli
    PROPERTIES
        OUTPUT_NAME "chassis"
)

target_include_directories(chassis_cli PRIVATE src)

target_sources(chassis_cli
    PRIVATE
        src/main.cpp
        src/infrastructure/logging/logger.cpp
        src/infrastructure/cli/cli.cpp
        src/infrastructure/cli/init_command.cpp
        src/infrastructure/cli/new_command.cpp
        src/infrastructure/cli/build_command.cpp
        src/infrastructure/cli/run_command.cpp
)

target_link_libraries(chassis_cli
    PRIVATE
        chassis::app
        CLI11::CLI11
        spdlog::spdlog
)

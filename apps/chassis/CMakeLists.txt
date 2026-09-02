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

add_library(chassis_cli_commands STATIC)
target_include_directories(chassis_cli_commands PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_sources(chassis_cli_commands
    PRIVATE
        src/commands/command.cpp
        src/commands/init.cpp
        src/commands/new.cpp
        src/commands/build.cpp
)

target_link_libraries(chassis_cli_commands
    PUBLIC
        chassis::core
        chassis::filesystem
        chassis::manifest
        chassis::process
        chassis::domain
        chassis::application
        chassis::infrastructure
        CLI11::CLI11
        spdlog::spdlog
)

add_executable(chassis_cli)
set_target_properties(chassis_cli
    PROPERTIES
        OUTPUT_NAME "chassis"
)
target_sources(chassis_cli PRIVATE src/main.cpp)
target_link_libraries(chassis_cli PRIVATE chassis_cli_commands)

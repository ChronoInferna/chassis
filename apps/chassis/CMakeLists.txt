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

add_executable(chassis_cli)
set_target_properties(chassis_cli
    PROPERTIES
        OUTPUT_NAME "chassis"
)

target_sources(chassis_cli
    PRIVATE
        src/main.cpp
        src/commands/init.cpp
)

target_link_libraries(chassis_cli
    PRIVATE
        chassis::core
        chassis::filesystem
        chassis::manifest
        CLI11::CLI11
        spdlog::spdlog
)

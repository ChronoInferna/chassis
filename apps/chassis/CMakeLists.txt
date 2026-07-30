include(FetchContent)

FetchContent_Declare(
    CLI11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG v2.6.2
)

FetchContent_MakeAvailable(CLI11)
# target_link_libraries(chassis PRIVATE CLI11::CLI11)

add_executable(chassis
    src/main.cpp
)

target_link_libraries(chassis
    PRIVATE
        # chassis::core
        # chassis::filesystem
        # chassis::manifest
        CLI11::CLI11
)

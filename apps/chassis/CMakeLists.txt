add_executable(chassis
    src/main.cpp
)

target_link_libraries(chassis
    PRIVATE
        # chassis_core
        # chassis_manifest
        # chassis_workspace
        CLI11::CLI11
)

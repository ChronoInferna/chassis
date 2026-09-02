add_library(chassis_filesystem STATIC)
add_library(chassis::filesystem ALIAS chassis_filesystem)

target_sources(chassis_filesystem
    PRIVATE
        src/chassis/filesystem/text_file.cpp
        src/chassis/filesystem/path.cpp
        src/chassis/filesystem/temp.cpp
        src/chassis/filesystem/io.cpp
        src/chassis/filesystem/std_filesystem.cpp

    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include"
        FILES
            include/chassis/filesystem/filesystem.hpp
            include/chassis/filesystem/std_filesystem.hpp
            include/chassis/filesystem/text_file.hpp
            include/chassis/filesystem/path.hpp
            include/chassis/filesystem/temp.hpp
            include/chassis/filesystem/io.hpp
)

target_link_libraries(chassis_filesystem
    PUBLIC
        chassis::core
)

target_compile_features(chassis_filesystem PUBLIC cxx_std_23)

set_target_properties(
    chassis_filesystem
    PROPERTIES VERIFY_INTERFACE_HEADER_SETS ${PROJECT_IS_TOP_LEVEL}
)

# Install the library
install(
    TARGETS chassis_filesystem
    EXPORT chassisTargets
    FILE_SET HEADERS
)

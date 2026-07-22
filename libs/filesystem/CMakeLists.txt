add_library(chassis_filesystem)
add_library(chassis::filesystem ALIAS chassis_filesystem)

target_sources(chassis_filesystem
    PRIVATE
        src/io.cpp
        src/path.cpp
        src/temp.cpp

    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include"
        FILES
            include/chassis/filesystem/filesystem.hpp
            include/chassis/filesystem/io.hpp
            include/chassis/filesystem/path.hpp
            include/chassis/filesystem/temp.hpp
)

target_link_libraries(chassis_filesystem
    PUBLIC
        chassis_core
)

target_compile_features(chassis_core PUBLIC cxx_std_23)

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

if(CHASSIS_BUILD_TESTS)
    add_subdirectory(tests/chassis/filesystem)
endif()

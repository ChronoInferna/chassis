#include <chassis/application/use_cases.hpp>

#include <filesystem>
#include <gtest/gtest.h>

namespace {

TEST(ApplicationUseCases, InitProjectCreatesManifest) {
  auto root = std::filesystem::temp_directory_path() /
              "chassis_application_init_project_test";
  std::filesystem::remove_all(root);
  std::filesystem::create_directories(root);

  auto result = chassis::application::init_project(root);

  EXPECT_TRUE(result.success);
  EXPECT_TRUE(std::filesystem::exists(root / "Chassis.toml"));

  std::filesystem::remove_all(root);
}

TEST(ApplicationUseCases, NewProjectCreatesProjectDirectory) {
  auto root = std::filesystem::temp_directory_path() /
              "chassis_application_new_project_test";
  std::filesystem::remove_all(root);
  std::filesystem::create_directories(root);

  auto result = chassis::application::new_project(root, "demo");

  EXPECT_TRUE(result.success);
  EXPECT_TRUE(std::filesystem::exists(root / "demo" / "Chassis.toml"));

  std::filesystem::remove_all(root);
}

TEST(ApplicationUseCases, BuildProjectFailsWithoutManifest) {
  auto root = std::filesystem::temp_directory_path() /
              "chassis_application_build_project_missing_manifest";
  std::filesystem::remove_all(root);
  std::filesystem::create_directories(root);

  auto result = chassis::application::build_project(root);

  EXPECT_FALSE(result.success);

  std::filesystem::remove_all(root);
}

} // namespace

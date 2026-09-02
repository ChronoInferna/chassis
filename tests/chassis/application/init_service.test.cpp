#include <gtest/gtest.h>

#include <application/init_service.hpp>
#include <chassis/filesystem/std_filesystem.hpp>
#include <chassis/manifest/toml_manifest_store.hpp>
#include <filesystem>

TEST(InitService, CreatesProjectSuccessfully) {
  auto temp_dir = std::filesystem::temp_directory_path() / "chassis_init_service_test_1";
  std::filesystem::remove_all(temp_dir);
  std::filesystem::create_directories(temp_dir);

  chassis::fs::StdFileSystem fs;
  chassis::manifest::TomlManifestStore manifest_store(fs);
  chassis::app::InitService init_service(fs, manifest_store);

  chassis::app::InitOptions options{.path = temp_dir, .name = "test_app"};
  auto result = init_service.init_project(options);

  ASSERT_TRUE(result.has_value());
  EXPECT_EQ(result->name(), "test_app");
  EXPECT_TRUE(fs.exists(result->manifest_path()));

  std::filesystem::remove_all(temp_dir);
}

TEST(InitService, FailsIfManifestAlreadyExists) {
  auto temp_dir = std::filesystem::temp_directory_path() / "chassis_init_service_test_2";
  std::filesystem::remove_all(temp_dir);
  std::filesystem::create_directories(temp_dir);

  chassis::fs::StdFileSystem fs;
  chassis::manifest::TomlManifestStore manifest_store(fs);
  chassis::app::InitService init_service(fs, manifest_store);

  chassis::app::InitOptions options{.path = temp_dir};
  auto result1 = init_service.init_project(options);
  ASSERT_TRUE(result1.has_value());

  auto result2 = init_service.init_project(options);
  EXPECT_FALSE(result2.has_value());

  std::filesystem::remove_all(temp_dir);
}

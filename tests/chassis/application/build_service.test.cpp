#include <gtest/gtest.h>

#include <application/build_service.hpp>
#include <application/init_service.hpp>
#include <application/project_service.hpp>
#include <chassis/builder/builder.hpp>
#include <chassis/filesystem/std_filesystem.hpp>
#include <chassis/manifest/toml_manifest_store.hpp>

class MockBuilder : public chassis::builder::Builder {
public:
  bool build_called = false;
  std::string last_preset;

  auto build(const chassis::manifest::Project &project,
             const chassis::builder::BuildOptions &options)
      -> chassis::error::Result<chassis::builder::BuildResult> override {
    build_called = true;
    last_preset = options.preset;
    return chassis::builder::BuildResult{
        .output = chassis::process::Output{.exit_code = 0}};
  }
};

TEST(BuildService, DelegatesToBuilderPort) {
  auto temp_dir = std::filesystem::temp_directory_path() / "chassis_build_service_test_1";
  std::filesystem::remove_all(temp_dir);
  std::filesystem::create_directories(temp_dir);

  chassis::fs::StdFileSystem fs;
  chassis::manifest::TomlManifestStore manifest_store(fs);
  chassis::app::InitService init_service(fs, manifest_store);
  chassis::app::ProjectService project_service(fs, manifest_store);

  auto init_res = init_service.init_project({.path = temp_dir, .name = "build_test_app"});
  ASSERT_TRUE(init_res.has_value());

  MockBuilder mock_builder;
  chassis::app::BuildService build_service(project_service, mock_builder);

  chassis::builder::BuildOptions options{.preset = "default"};
  auto build_res = build_service.build(init_res->path, options);

  ASSERT_TRUE(build_res.has_value());
  EXPECT_TRUE(mock_builder.build_called);
  EXPECT_EQ(mock_builder.last_preset, "default");

  std::filesystem::remove_all(temp_dir);
}

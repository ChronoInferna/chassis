#include <gtest/gtest.h>

#include <application/build_service.hpp>
#include <application/init_service.hpp>
#include <application/project_service.hpp>
#include <application/run_service.hpp>
#include <chassis/builder/builder.hpp>
#include <chassis/filesystem/std_filesystem.hpp>
#include <chassis/manifest/toml_manifest_store.hpp>
#include <chassis/process/process_runner.hpp>

class MockBuilderForRun : public chassis::builder::Builder {
public:
  bool build_called = false;

  auto build(const chassis::manifest::Project &project,
             const chassis::builder::BuildOptions &options)
      -> chassis::error::Result<chassis::builder::BuildResult> override {
    build_called = true;
    return chassis::builder::BuildResult{
        .output = chassis::process::Output{.exit_code = 0}};
  }
};

class MockProcessRunner : public chassis::process::ProcessRunner {
public:
  bool run_called = false;

  auto run(const chassis::process::Command &command)
      -> chassis::error::Result<chassis::process::Output> override {
    run_called = true;
    return chassis::process::Output{.exit_code = 0};
  }
};

TEST(RunService, ComposesBuildServiceAndExecutes) {
  auto temp_dir = std::filesystem::temp_directory_path() / "chassis_run_service_test_1";
  std::filesystem::remove_all(temp_dir);
  std::filesystem::create_directories(temp_dir);

  chassis::fs::StdFileSystem fs;
  chassis::manifest::TomlManifestStore manifest_store(fs);
  chassis::app::InitService init_service(fs, manifest_store);
  chassis::app::ProjectService project_service(fs, manifest_store);

  auto init_res = init_service.init_project({.path = temp_dir, .name = "run_test_app"});
  ASSERT_TRUE(init_res.has_value());

  MockBuilderForRun mock_builder;
  chassis::app::BuildService build_service(project_service, mock_builder);
  MockProcessRunner mock_runner;

  chassis::app::RunService run_service(project_service, build_service, mock_runner);

  chassis::app::RunOptions options{.path = init_res->path, .preset = "default"};
  auto run_res = run_service.run(options);

  ASSERT_TRUE(run_res.has_value());
  EXPECT_TRUE(mock_builder.build_called);
  EXPECT_TRUE(mock_runner.run_called);

  std::filesystem::remove_all(temp_dir);
}

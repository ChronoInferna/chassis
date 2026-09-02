#include "build.hpp"

#include <chassis/filesystem/path.hpp>
#include <chassis/manifest/manifest.hpp>
#include <chassis/process/process.hpp>
#include <memory>
#include <spdlog/spdlog.h>

auto add_build_command(CLI::App &app) -> void {
  auto options = std::make_shared<BuildOptions>();
  auto *build_cmd =
      app.add_subcommand("build", "Build a project from the manifest file");

  build_cmd->add_option("-p,--path", options->path,
                        "Project path that contains Chassis.toml");
  build_cmd->callback([options]() { run_build_command(*options); });
}

auto run_build_command(const BuildOptions &options) -> void {
  auto parent_path = options.path;
  auto manifest_path = parent_path / "Chassis.toml";

  if (!chassis::fs::exists(manifest_path)) {
    spdlog::error("Manifest file does not exist at path: {}",
                  manifest_path.string());
    return;
  }

  auto validate_res = chassis::manifest::validate(manifest_path);
  if (!validate_res) {
    spdlog::error("Manifest validation failed: {} at {}:{}",
                  validate_res.error().message(),
                  validate_res.error().location().file_name(),
                  validate_res.error().location().line());
    return;
  }

  auto read_res = chassis::manifest::read_manifest(manifest_path);
  if (!read_res) {
    spdlog::error("Failed to read manifest file: {} at {}:{}",
                  read_res.error().message(),
                  read_res.error().location().file_name(),
                  read_res.error().location().line());
    return;
  }

  chassis::process::Command cmake = {
      .program = "cmake",
      .arguments = {"--workflow", "--preset", "debug"}};
  auto run_res = chassis::process::run(cmake);

  if (!run_res) {
    spdlog::error("Failed to run cmake: {} at {}:{}", run_res.error().message(),
                  run_res.error().location().file_name(),
                  run_res.error().location().line());
    return;
  }

  if (!run_res->succeeded()) {
    spdlog::error("Build failed with exit code: {}", run_res->exit_code);
    return;
  }

  spdlog::info("Build completed with exit code: {}", run_res->exit_code);
}

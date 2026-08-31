#include "build.hpp"

#include <CLI/CLI.hpp>
#include <chassis/filesystem/path.hpp>
#include <chassis/manifest/manifest.hpp>
#include <chassis/process/process.hpp>
#include <memory>
#include <spdlog/spdlog.h>

// TODO template this?
// auto add_command<CommandOptions T>(CLI::App &app, std::function<void> cmd) ->
// void {
auto add_build_command(CLI::App &app) -> void {
  auto options = std::make_shared<BuildOptions>();
  auto *build_cmd =
      app.add_subcommand("build", "Build a project from the manifest file");

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

  spdlog::info("Reading manifest file at path: {}", manifest_path.string());
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
      .arguments = {
          "--workflow", "--preset",
          "debug"}}; // TODO build instead of debug? potential presets: build,
                     // build-release, run, run-release, test, test-release
  auto run_res = chassis::process::run(cmake);
  spdlog::info("Running cmake with exit code: {}", run_res->exit_code);
  if (!run_res) {
    spdlog::error("Failed to run cmake: {} at {}:{}", run_res.error().message(),
                  run_res.error().location().file_name(),
                  run_res.error().location().line());
    return;
  }
}

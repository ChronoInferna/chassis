#include "new.hpp"

#include <CLI/CLI.hpp>
#include <chassis/core/error/error.hpp>
#include <chassis/filesystem/path.hpp>
#include <chassis/manifest/manifest.hpp>
#include <spdlog/spdlog.h>

auto add_new_command(CLI::App &app) -> void {
  auto options = std::make_shared<NewOptions>();
  auto *new_cmd = app.add_subcommand("new", "Create a new Chassis project");

  new_cmd->callback([options]() { run_new_command(*options); });
  // TODO add option for project name, default to error
}

auto run_new_command(const NewOptions &options) -> void {
  auto parent_path = options.path / options.project_name;
  auto manifest_path = parent_path / "Chassis.toml";

  if (chassis::fs::exists(manifest_path)) {
    spdlog::error("Manifest file already exists at: {}",
                  manifest_path.string());
    return;
  }

  auto manifest = chassis::manifest::create(parent_path.filename().native());
  spdlog::debug("Creating manifest at: {}", (manifest_path).string());

  auto res = chassis::manifest::write_manifest(manifest_path, manifest);
  spdlog::debug("Manifest created successfully");

  if (!res) {
    spdlog::error("Failed to create manifest file: {} at {}:{}",
                  res.error().message(), res.error().location().file_name(),
                  res.error().location().line());
    return;
  }

  spdlog::info("Project successfully created at: {}", manifest_path.string());
}

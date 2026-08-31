#include "init.hpp"

#include <CLI/CLI.hpp>
#include <chassis/filesystem/path.hpp>
#include <chassis/manifest/manifest.hpp>
#include <memory>
#include <spdlog/spdlog.h>

auto add_init_command(CLI::App &app) -> void {
  auto options = std::make_shared<InitOptions>();
  auto *init_cmd =
      app.add_subcommand("init", "Initialize a new Chassis project");

  init_cmd->callback([options]() { run_init_command(*options); });
}

auto run_init_command(const InitOptions &options) -> void {
  auto parent_path = options.path;
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
    // TODO macro?
    spdlog::error("Failed to create manifest file: {} at {}:{}",
                  res.error().message(), res.error().location().file_name(),
                  res.error().location().line());
    return;
  }

  spdlog::info("Project successfully initialized at: {}",
               manifest_path.string());
}

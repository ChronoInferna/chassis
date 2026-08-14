#include "init.hpp"
#include "chassis/filesystem/path.hpp"

#include <CLI/CLI.hpp>
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
  auto manifest_path = options.path / "Chassis.toml";
  auto parent_folder = options.path.filename().native();

  if (chassis::fs::exists(manifest_path)) {
    spdlog::error("Manifest file already exists at: {}",
                  manifest_path.string());
    return;
  }

  auto manifest = chassis::manifest::create(parent_folder);
  spdlog::debug("Creating manifest at: {}", (manifest_path).string());

  auto res = chassis::manifest::write_manifest(options.path, manifest);
  spdlog::debug("Manifest created successfully");

  if (!res) {
    spdlog::error("Failed to create manifest file: {}", res.error().message());
  }

  spdlog::info("Project initialized successfully at: {}",
               options.path.string());
}

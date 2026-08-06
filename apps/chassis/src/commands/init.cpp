#include "init.hpp"

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
  auto manifest = chassis::manifest::create("my_project");
  spdlog::debug("Creating manifest at: {}",
                (options.path / "Chassis.toml").string());
  auto res = chassis::manifest::write_manifest(options.path, manifest);
  spdlog::debug("Manifest created successfully.");

  if (!res) {
    spdlog::error("Failed to create manifest: {}", res.error().message());
  }

  spdlog::info("Project initialized successfully at: {}",
               options.path.string());
}

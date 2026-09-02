#include "new.hpp"

#include <chassis/filesystem/path.hpp>
#include <chassis/manifest/manifest.hpp>
#include <memory>
#include <spdlog/spdlog.h>

auto add_new_command(CLI::App &app) -> void {
  auto options = std::make_shared<NewOptions>();
  auto *new_cmd = app.add_subcommand("new", "Create a new Chassis project");

  new_cmd
      ->add_option("project-name", options->project_name,
                   "Name of the project to create")
      ->required();
  new_cmd->add_option("-p,--path", options->path,
                      "Parent path where the project should be created");
  new_cmd->callback([options]() { run_new_command(*options); });
}

auto run_new_command(const NewOptions &options) -> void {
  auto parent_path = options.path / options.project_name;
  auto manifest_path = parent_path / "Chassis.toml";

  if (chassis::fs::exists(manifest_path)) {
    spdlog::error("Manifest file already exists at: {}",
                  manifest_path.string());
    return;
  }

  if (!chassis::fs::exists(parent_path)) {
    auto create_res = chassis::fs::create_directory(parent_path);
    if (!create_res) {
      spdlog::error("Failed to create project directory: {} at {}:{}",
                    create_res.error().message(),
                    create_res.error().location().file_name(),
                    create_res.error().location().line());
      return;
    }
  }

  auto manifest = chassis::manifest::create(parent_path.filename().native());
  auto res = chassis::manifest::write_manifest(manifest_path, manifest);

  if (!res) {
    spdlog::error("Failed to create manifest file: {} at {}:{}",
                  res.error().message(), res.error().location().file_name(),
                  res.error().location().line());
    return;
  }

  spdlog::info("Project successfully created at: {}", manifest_path.string());
}

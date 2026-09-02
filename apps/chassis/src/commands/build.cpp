#include "build.hpp"

#include "result.hpp"

#include <chassis/application/use_cases.hpp>

#include <memory>

auto add_build_command(CLI::App &app) -> void {
  auto options = std::make_shared<BuildOptions>();
  auto *build_cmd =
      app.add_subcommand("build", "Build a project from the manifest file");

  build_cmd->add_option("-p,--path", options->path,
                        "Project path that contains Chassis.toml");
  build_cmd->callback([options]() { run_build_command(*options); });
}

auto run_build_command(const BuildOptions &options) -> void {
  render_command_result(chassis::application::build_project(options.path));
}

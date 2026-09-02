#include "init.hpp"

#include "result.hpp"

#include <chassis/application/use_cases.hpp>

#include <memory>

auto add_init_command(CLI::App &app) -> void {
  auto options = std::make_shared<InitOptions>();
  auto *init_cmd =
      app.add_subcommand("init", "Initialize a new Chassis project");

  init_cmd->add_option("-p,--path", options->path,
                       "Path where the manifest should be created");
  init_cmd->callback([options]() { run_init_command(*options); });
}

auto run_init_command(const InitOptions &options) -> void {
  render_command_result(chassis::application::init_project(options.path));
}

#include "build.hpp"

#include "command.hpp"

#include <memory>

auto add_build_command(CLI::App &app, CommandContext &context) -> void {
  auto options = std::make_shared<BuildOptions>();
  auto *build_cmd =
      app.add_subcommand("build", "Build a project from the manifest file");

  build_cmd->add_option("-p,--path", options->path,
                        "Project path that contains Chassis.toml");

  build_cmd->callback([options, &context]() {
    render_command_result(context.build_use_case.run(options->path));
  });
}

#include "init.hpp"

#include "command.hpp"

#include <memory>

auto add_init_command(CLI::App &app, CommandContext &context) -> void {
  auto options = std::make_shared<InitOptions>();
  auto *init_cmd =
      app.add_subcommand("init", "Initialize a new Chassis project");

  init_cmd->add_option("-p,--path", options->path,
                       "Path where the manifest should be created");

  init_cmd->callback([options, &context]() {
    render_command_result(context.init_use_case.run(options->path));
  });
}

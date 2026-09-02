#include "new.hpp"

#include "command.hpp"

#include <memory>

auto add_new_command(CLI::App &app, CommandContext &context) -> void {
  auto options = std::make_shared<NewOptions>();
  auto *new_cmd = app.add_subcommand("new", "Create a new Chassis project");

  new_cmd
      ->add_option("project-name", options->project_name,
                   "Name of the project to create")
      ->required();
  new_cmd->add_option("-p,--path", options->path,
                      "Parent path where the project should be created");

  new_cmd->callback([options, &context]() {
    render_command_result(
        context.new_use_case.run(options->path, options->project_name));
  });
}

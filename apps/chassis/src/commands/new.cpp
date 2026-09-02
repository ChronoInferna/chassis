#include "new.hpp"

#include "result.hpp"

#include <chassis/application/use_cases.hpp>

#include <memory>

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
  render_command_result(
      chassis::application::new_project(options.path, options.project_name));
}

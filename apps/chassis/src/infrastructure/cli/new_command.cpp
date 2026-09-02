#include "infrastructure/cli/new_command.hpp"

#include <CLI/CLI.hpp>
#include <memory>
#include <spdlog/spdlog.h>

namespace chassis::infra::cli {

auto add_new_command(CLI::App &app, app::InitService &init_service) -> void {
  auto options = std::make_shared<chassis::app::InitOptions>();
  auto *new_cmd = app.add_subcommand("new", "Create a new Chassis project");

  // TODO logging for "name is required"?
  new_cmd->add_option("name", options->name, "Project name")->required();
  new_cmd->add_option("-p,--path", options->path,
                      "Base path for the new project");

  new_cmd->callback([options, &init_service]() {
    auto res = init_service.init_project(*options);
    if (!res) {
      spdlog::error("Failed to create project: {} at {}:{}",
                    res.error().message(), res.error().location().file_name(),
                    res.error().location().line());
      return;
    }
    spdlog::info("Project successfully created at: {}",
                 res->manifest_path().string());
  });
}

} // namespace chassis::infra::cli

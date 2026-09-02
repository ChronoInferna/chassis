#include "infrastructure/cli/init_command.hpp"

#include <CLI/CLI.hpp>
#include <memory>
#include <spdlog/spdlog.h>

namespace chassis::infra::cli {

auto add_init_command(CLI::App &app, app::InitService &init_service) -> void {
  auto options = std::make_shared<chassis::app::InitOptions>();
  auto *init_cmd =
      app.add_subcommand("init", "Initialize a new Chassis project");

  init_cmd->add_option("-p,--path", options->path,
                       "Path to initialize project in");

  init_cmd->callback([options, &init_service]() {
    auto res = init_service.init_project(*options);
    if (!res) {
      spdlog::error("Failed to initialize project: {} at {}:{}",
                    res.error().message(), res.error().location().file_name(),
                    res.error().location().line());
      return;
    }
    spdlog::info("Project successfully initialized at: {}",
                 res->manifest_path().string());
  });
}

} // namespace chassis::infra::cli

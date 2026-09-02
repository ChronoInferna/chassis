#include "infrastructure/cli/run_command.hpp"

#include <CLI/CLI.hpp>
#include <memory>
#include <spdlog/spdlog.h>

namespace chassis::infra::cli {

auto add_run_command(CLI::App &app, app::RunService &run_service) -> void {
  auto options = std::make_shared<chassis::app::RunOptions>();
  auto *run_cmd =
      app.add_subcommand("run", "Build and run a Chassis project");

  run_cmd->add_option("-p,--path", options->path, "Path to project root");
  run_cmd->add_option("--preset", options->preset, "CMake workflow preset")
      ->capture_default_str();
  run_cmd->add_option("args", options->args, "Arguments passed to the executable");

  run_cmd->callback([options, &run_service]() {
    spdlog::info("Running project at path: {}", options->path.string());
    auto res = run_service.run(*options);
    if (!res) {
      spdlog::error("Failed to run project: {} at {}:{}",
                    res.error().message(), res.error().location().file_name(),
                    res.error().location().line());
      return;
    }
    spdlog::info("Project finished with exit code: {}",
                 res->run_output.exit_code);
  });
}

} // namespace chassis::infra::cli

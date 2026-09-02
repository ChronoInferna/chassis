#include "infrastructure/cli/build_command.hpp"

#include <CLI/CLI.hpp>
#include <memory>
#include <spdlog/spdlog.h>

namespace chassis::infra::cli {

struct BuildCLIOptions {
  std::filesystem::path path = std::filesystem::current_path();
  std::string preset = "default";
};

auto add_build_command(CLI::App &app, app::BuildService &build_service)
    -> void {
  auto options = std::make_shared<BuildCLIOptions>();
  auto *build_cmd =
      app.add_subcommand("build", "Build a project from the manifest file");

  build_cmd->add_option("-p,--path", options->path, "Path to project root");
  build_cmd->add_option("--preset", options->preset, "CMake workflow preset")
      ->capture_default_str();

  build_cmd->callback([options, &build_service]() {
    spdlog::info("Building project at path: {}", options->path.string());

    chassis::builder::BuildOptions build_opts{.preset = options->preset};
    auto res = build_service.build(options->path, build_opts);

    if (!res) {
      spdlog::error("Failed to build project: {} at {}:{}",
                    res.error().message(), res.error().location().file_name(),
                    res.error().location().line());
      return;
    }
    spdlog::info("Running cmake with exit code: {}", res->output.exit_code);
  });
}

} // namespace chassis::infra::cli

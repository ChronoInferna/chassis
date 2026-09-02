#include "command.hpp"

#include "build.hpp"
#include "init.hpp"
#include "new.hpp"

#include <spdlog/spdlog.h>

namespace {

const auto kCommandModules = std::array{
    CommandModule{"init", "Initialize a new Chassis project",
                  &add_init_command},
    CommandModule{"new", "Create a new Chassis project", &add_new_command},
    CommandModule{"build", "Build a project from the manifest file",
                  &add_build_command},
};

} // namespace

CommandContext::CommandContext()
    : manifest_store{}, process_runner{}, project_generator{manifest_store},
      init_use_case{project_generator}, new_use_case{project_generator},
      build_use_case{manifest_store, process_runner} {}

auto render_command_result(const chassis::application::CommandResult &result)
    -> void {
  if (result.success) {
    spdlog::info("{}", result.message);
    return;
  }

  if (result.error.has_value()) {
    spdlog::error("{}: {}", result.message, result.error->as_text());
    return;
  }

  spdlog::error("{}", result.message);
}

auto command_modules() -> std::span<const CommandModule> {
  return std::span<const CommandModule>{kCommandModules};
}

auto register_all_commands(CLI::App &app) -> void {
  static auto context = CommandContext{};

  for (const auto &module : command_modules()) {
    module.register_command(app, context);
  }
}

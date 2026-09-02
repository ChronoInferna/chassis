#include "result.hpp"

#include <spdlog/spdlog.h>

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

#pragma once

#include "application/run_service.hpp"
#include <CLI/CLI.hpp>

namespace chassis::infra::cli {

auto add_run_command(CLI::App &app, app::RunService &run_service) -> void;

} // namespace chassis::infra::cli

#pragma once

#include "application/build_service.hpp"
#include <CLI/CLI.hpp>

namespace chassis::infra::cli {

auto add_build_command(CLI::App &app, app::BuildService &build_service) -> void;

} // namespace chassis::infra::cli

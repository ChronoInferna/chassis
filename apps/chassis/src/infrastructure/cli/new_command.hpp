#pragma once

#include "application/init_service.hpp"
#include <CLI/CLI.hpp>

namespace chassis::infra::cli {

auto add_new_command(CLI::App &app, app::InitService &init_service) -> void;

} // namespace chassis::infra::cli

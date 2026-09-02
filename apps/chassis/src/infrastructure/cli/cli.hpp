#pragma once

#include "application/build_service.hpp"
#include "application/init_service.hpp"
#include "application/run_service.hpp"
#include <CLI/CLI.hpp>

namespace chassis::infra::cli {

auto setup_cli(CLI::App &app, app::InitService &init_service,
               app::BuildService &build_service, app::RunService &run_service)
    -> void;

} // namespace chassis::infra::cli

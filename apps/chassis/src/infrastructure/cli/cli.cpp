#include "infrastructure/cli/cli.hpp"

#include "infrastructure/cli/build_command.hpp"
#include "infrastructure/cli/init_command.hpp"
#include "infrastructure/cli/new_command.hpp"
#include "infrastructure/cli/run_command.hpp"

namespace chassis::infra::cli {

auto setup_cli(CLI::App &app, app::InitService &init_service,
               app::BuildService &build_service, app::RunService &run_service)
    -> void {
  add_init_command(app, init_service);
  // TODO new service involving new folder
  add_new_command(app, init_service);
  // TODO just build, no test
  add_build_command(app, build_service);
  // TODO build if necessary(?, see if rust does it) + run, no test
  add_run_command(app, run_service);
  // TODO test command
}

} // namespace chassis::infra::cli

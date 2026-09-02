#include "application/run_service.hpp"
#include <chassis/filesystem/path.hpp>

namespace chassis::app {

auto RunService::run(const RunOptions &options) -> Result<RunResult> {
  CHASSIS_TRY_VALUE(project, project_service_.find_and_load_project(options.path));

  builder::BuildOptions build_opts{.preset = options.preset};
  CHASSIS_TRY_VALUE(b_result, build_service_.build(project, build_opts));

  fs::Path exe_path = project.path / "build" / "bin" / project.name();
  if (!fs::exists(exe_path)) {
    exe_path = project.path / "bin" / project.name();
  }
  if (!fs::exists(exe_path)) {
    exe_path = project.path / project.name();
  }

  process::Command run_cmd = {
      .program = exe_path,
      .arguments = options.args,
      .working_directory = project.path,
  };

  CHASSIS_TRY_VALUE(r_output, process_runner_.run(run_cmd));

  return RunResult{
      .build_result = b_result,
      .run_output = r_output,
  };
}

} // namespace chassis::app

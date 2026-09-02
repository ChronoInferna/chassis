#include "application/build_service.hpp"

namespace chassis::app {

auto BuildService::build(const fs::Path &path,
                          const builder::BuildOptions &options)
    -> Result<builder::BuildResult> {
  CHASSIS_TRY_VALUE(project, project_service_.find_and_load_project(path));
  return build(project, options);
}

auto BuildService::build(const manifest::Project &project,
                          const builder::BuildOptions &options)
    -> Result<builder::BuildResult> {
  CHASSIS_TRY_VALUE(res, builder_.build(project, options));

  if (!res.output.succeeded()) {
    return make_error(ErrorCode::ProcessError);
  }

  return res;
}

} // namespace chassis::app

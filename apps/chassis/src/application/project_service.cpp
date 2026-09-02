#include "application/project_service.hpp"

namespace chassis::app {

auto ProjectService::load_project(const fs::Path &project_dir)
    -> Result<manifest::Project> {
  fs::Path manifest_path = project_dir;
  if (manifest_path.filename() != "Chassis.toml") {
    manifest_path = project_dir / "Chassis.toml";
  }

  if (!fs_.exists(manifest_path)) {
    return make_error(ErrorCode::MissingFile);
  }

  CHASSIS_TRY_VALUE(manifest, manifest_store_.read(manifest_path));

  fs::Path project_path = manifest_path.parent_path();
  return manifest::Project{
      .path = project_path,
      .manifest = manifest,
  };
}

auto ProjectService::find_and_load_project(const fs::Path &start_path)
    -> Result<manifest::Project> {
  fs::Path manifest_path = start_path;
  if (!fs_.exists(manifest_path) || manifest_path.filename() != "Chassis.toml") {
    CHASSIS_TRY_VALUE(found, fs_.find_upward(start_path, "Chassis.toml"));
    manifest_path = found;
  }

  return load_project(manifest_path);
}

} // namespace chassis::app

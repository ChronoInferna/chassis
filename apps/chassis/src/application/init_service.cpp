#include "application/init_service.hpp"

namespace chassis::app {

auto InitService::init_project(const InitOptions &options)
    -> Result<manifest::Project> {
  fs::Path target_dir = options.path;

  if (!options.name.empty()) {
    target_dir = target_dir / options.name;
  }

  fs::Path manifest_path = target_dir / "Chassis.toml";

  if (fs_.exists(manifest_path)) {
    return make_error(ErrorCode::InvalidArgument);
  }

  if (!fs_.exists(target_dir)) {
    CHASSIS_TRY(fs_.create_directory(target_dir));
  }

  std::string project_name = options.name;
  if (project_name.empty()) {
    project_name = target_dir.filename().string();
    if (project_name.empty() || project_name == ".") {
      CHASSIS_TRY_VALUE(canonical_path, fs_.canonical(target_dir));
      project_name = canonical_path.filename().string();
    }
  }

  manifest::Manifest manifest = chassis::manifest::create(project_name);
  CHASSIS_TRY(manifest_store_.write(manifest_path, manifest));

  return manifest::Project{
      .path = target_dir,
      .manifest = manifest,
  };
}

} // namespace chassis::app

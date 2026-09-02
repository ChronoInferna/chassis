#include <chassis/infrastructure/project/basic_project_generator.hpp>

#include <chassis/filesystem/path.hpp>

namespace chassis::infrastructure::project {

auto BasicProjectGenerator::generate(const domain::project::ProjectSpec &project)
    -> error::Result<void> {
  if (manifest_store_.exists(project.manifest_path)) {
    return error::make_error(error::ErrorCode::InvalidArgument);
  }

  if (project.create_root_directory && !fs::exists(project.root_path)) {
    CHASSIS_TRY(fs::create_directory(project.root_path));
  }

  auto manifest = manifest_store_.create_default(project.package_name);
  CHASSIS_TRY(manifest_store_.write(project.manifest_path, manifest));

  return {};
}

} // namespace chassis::infrastructure::project

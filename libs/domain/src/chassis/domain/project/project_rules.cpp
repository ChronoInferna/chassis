#include <chassis/domain/project/project_rules.hpp>

namespace chassis::domain::project {

namespace {
constexpr auto kManifestName = "Chassis.toml";
}

auto resolve_init_project(const fs::Path &path) -> error::Result<ProjectSpec> {
  if (path.empty()) {
    return error::make_error(error::ErrorCode::InvalidArgument);
  }

  auto normalized_path = path;

  return ProjectSpec{
      .root_path = normalized_path,
      .manifest_path = normalized_path / kManifestName,
      .package_name = normalized_path.filename().native(),
      .create_root_directory = false,
  };
}

auto resolve_new_project(const fs::Path &parent_path,
                         const std::string &project_name)
    -> error::Result<ProjectSpec> {
  if (parent_path.empty() || project_name.empty()) {
    return error::make_error(error::ErrorCode::InvalidArgument);
  }

  auto root_path = parent_path / project_name;

  return ProjectSpec{
      .root_path = root_path,
      .manifest_path = root_path / kManifestName,
      .package_name = project_name,
      .create_root_directory = true,
  };
}

} // namespace chassis::domain::project

#pragma once

#include <chassis/core/error/error.hpp>
#include <chassis/filesystem/path.hpp>

#include <string>

namespace chassis::domain::project {

struct ProjectSpec {
  fs::Path root_path;
  fs::Path manifest_path;
  std::string package_name;
  bool create_root_directory = false;
};

[[nodiscard]]
auto resolve_init_project(const fs::Path &path) -> error::Result<ProjectSpec>;

[[nodiscard]]
auto resolve_new_project(const fs::Path &parent_path,
                         const std::string &project_name)
    -> error::Result<ProjectSpec>;

} // namespace chassis::domain::project

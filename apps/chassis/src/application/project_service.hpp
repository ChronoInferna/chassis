#pragma once

#include <chassis/core/error/error.hpp>
#include <chassis/filesystem/filesystem.hpp>
#include <chassis/manifest/manifest_store.hpp>
#include <chassis/manifest/project.hpp>

namespace chassis::app {

using namespace chassis::error;

class ProjectService {
public:
  ProjectService(fs::FileSystem &fs, manifest::ManifestStore &manifest_store)
      : fs_(fs), manifest_store_(manifest_store) {}

  auto load_project(const fs::Path &project_dir) -> Result<manifest::Project>;
  auto find_and_load_project(const fs::Path &start_path)
      -> Result<manifest::Project>;

private:
  fs::FileSystem &fs_;
  manifest::ManifestStore &manifest_store_;
};

} // namespace chassis::app

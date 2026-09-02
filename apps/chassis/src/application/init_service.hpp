#pragma once

#include <chassis/core/error/error.hpp>
#include <chassis/filesystem/filesystem.hpp>
#include <chassis/manifest/manifest_store.hpp>
#include <chassis/manifest/project.hpp>

namespace chassis::app {

using namespace chassis::error;

struct InitOptions {
  fs::Path path = std::filesystem::current_path();
  std::string name;
};

class InitService {
public:
  InitService(fs::FileSystem &fs, manifest::ManifestStore &manifest_store)
      : fs_(fs), manifest_store_(manifest_store) {}

  auto init_project(const InitOptions &options) -> Result<manifest::Project>;

private:
  fs::FileSystem &fs_;
  manifest::ManifestStore &manifest_store_;
};

} // namespace chassis::app

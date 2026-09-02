#pragma once

#include <chassis/filesystem/filesystem.hpp>
#include <chassis/manifest/manifest_store.hpp>

namespace chassis::manifest {

class TomlManifestStore : public ManifestStore {
public:
  TomlManifestStore() = default;
  explicit TomlManifestStore(fs::FileSystem &fs) : fs_(&fs) {}

  [[nodiscard]] auto read(const fs::Path &path) const
      -> Result<Manifest> override;
  auto write(const fs::Path &path, const Manifest &manifest)
      -> Result<void> override;

private:
  std::unique_ptr<fs::FileSystem> fs_ = nullptr;
};

} // namespace chassis::manifest

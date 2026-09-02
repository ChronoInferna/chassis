#pragma once

#include <chassis/core/error/error.hpp>
#include <chassis/filesystem/path.hpp>
#include <chassis/manifest/manifest.hpp>

namespace chassis::manifest {

using namespace chassis::error;

class ManifestStore {
public:
  virtual ~ManifestStore() = default;

  [[nodiscard]] virtual auto read(const fs::Path &path) const
      -> Result<Manifest> = 0;
  virtual auto write(const fs::Path &path, const Manifest &manifest)
      -> Result<void> = 0;
};

} // namespace chassis::manifest

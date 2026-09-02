#pragma once

#include <chassis/core/error/error.hpp>
#include <chassis/filesystem/path.hpp>
#include <chassis/manifest/manifest.hpp>

namespace chassis::application::ports {

class ManifestStore {
public:
  virtual ~ManifestStore() = default;

  [[nodiscard]] virtual auto exists(const fs::Path &path) const -> bool = 0;

  [[nodiscard]] virtual auto create_default(std::string_view package_name) const
      -> manifest::Manifest = 0;

  virtual auto write(const fs::Path &path, const manifest::Manifest &manifest)
      -> error::Result<void> = 0;

  [[nodiscard]] virtual auto read(const fs::Path &path) const
      -> error::Result<manifest::Manifest> = 0;

  [[nodiscard]] virtual auto validate(const fs::Path &path) const
      -> error::Result<void> = 0;
};

} // namespace chassis::application::ports

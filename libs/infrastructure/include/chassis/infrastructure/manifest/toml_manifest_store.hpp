#pragma once

#include <chassis/application/ports/manifest_store.hpp>

namespace chassis::infrastructure::manifest {

class TomlManifestStore : public application::ports::ManifestStore {
public:
  [[nodiscard]] auto exists(const fs::Path &path) const -> bool override;

  [[nodiscard]] auto create_default(std::string_view package_name) const
      -> chassis::manifest::Manifest override;

  auto write(const fs::Path &path,
             const chassis::manifest::Manifest &manifest)
      -> error::Result<void> override;

  [[nodiscard]] auto read(const fs::Path &path) const
      -> error::Result<chassis::manifest::Manifest> override;

  [[nodiscard]] auto validate(const fs::Path &path) const
      -> error::Result<void> override;
};

} // namespace chassis::infrastructure::manifest

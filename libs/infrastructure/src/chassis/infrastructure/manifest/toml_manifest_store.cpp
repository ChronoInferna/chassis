#include <chassis/infrastructure/manifest/toml_manifest_store.hpp>

#include <chassis/filesystem/io.hpp>
#include <chassis/manifest/manifest.hpp>

namespace chassis::infrastructure::manifest {

auto TomlManifestStore::exists(const fs::Path &path) const -> bool {
  return fs::exists(path);
}

auto TomlManifestStore::create_default(std::string_view package_name) const
    -> chassis::manifest::Manifest {
  return chassis::manifest::create(package_name);
}

auto TomlManifestStore::write(const fs::Path &path,
                              const chassis::manifest::Manifest &manifest)
    -> error::Result<void> {
  return chassis::manifest::write_manifest(path, manifest);
}

auto TomlManifestStore::read(const fs::Path &path) const
    -> error::Result<chassis::manifest::Manifest> {
  return chassis::manifest::read_manifest(path);
}

auto TomlManifestStore::validate(const fs::Path &path) const
    -> error::Result<void> {
  return chassis::manifest::validate(path);
}

} // namespace chassis::infrastructure::manifest

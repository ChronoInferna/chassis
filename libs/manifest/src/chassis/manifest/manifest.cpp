#include <chassis/manifest/manifest.hpp>
#include <chassis/manifest/toml_manifest_store.hpp>

namespace chassis::manifest {

auto create(std::string_view package_name) -> Manifest {
  return Manifest{
      .package =
          Package{
              .name = std::string{package_name},
              .version = "0.1.0",
          },
  };
}

auto write_manifest(const fs::Path &path, const Manifest &manifest)
    -> Result<void> {
  TomlManifestStore store;
  return store.write(path, manifest);
}

auto read_manifest(const fs::Path &path) -> Result<Manifest> {
  TomlManifestStore store;
  return store.read(path);
}

auto validate(const fs::Path &path) -> Result<void> { return {}; }

} // namespace chassis::manifest

#include <chassis/manifest/manifest.hpp>

#include <toml++/toml.hpp>

namespace chassis::manifest {

auto create(std::string_view package_name) -> Manifest {}

auto write_manifest(const fs::Path &path, const Manifest &manifest)
    -> Result<void> {
  toml::table table{};

  table["package"] = toml::table{
      {"name", manifest.package.name},
      {"version", manifest.package.version},
  };
}

// auto validate(const fs::Path &path) -> bool {}

} // namespace chassis::manifest

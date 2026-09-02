#pragma once

#include <chassis/filesystem/path.hpp>
#include <chassis/manifest/manifest.hpp>
#include <string>

namespace chassis::manifest {

struct Project {
  fs::Path path;
  Manifest manifest;

  [[nodiscard]] auto name() const -> std::string {
    return manifest.package.name;
  }

  [[nodiscard]] auto manifest_path() const -> fs::Path {
    return path / "Chassis.toml";
  }
};

} // namespace chassis::manifest

#pragma once

#include <chassis/core/error/error.hpp>
#include <chassis/filesystem/filesystem.hpp>

#include <string>
#include <vector>

namespace chassis::manifest {

using namespace chassis::error;

struct Package {
  std::string name;
  std::string version = "0.1.0";
};

struct Manifest {
  Package package;
  std::vector<Package> dependencies;
};

auto create(std::string_view package_name) -> Manifest;

auto write_manifest(const fs::Path &path, const Manifest &manifest)
    -> Result<void>;

auto read_manifest(const fs::Path &path) -> Result<Manifest>;

auto update_manifest(const fs::Path &path, const Manifest &manifest)
    -> Result<void>;

auto validate(const fs::Path &path) -> Result<void>;

auto validate_manifest(const Manifest &manifest) -> Result<void>;

} // namespace chassis::manifest

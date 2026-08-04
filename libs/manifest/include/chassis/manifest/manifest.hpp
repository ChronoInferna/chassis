#pragma once

#include <chassis/core/error/error.hpp>
#include <chassis/filesystem/filesystem.hpp>

#include <string>

namespace chassis::manifest {

using namespace chassis::error;

struct Package {
  std::string name;
  std::string version = "0.1.0";
};

struct Manifest {
  Package package;
};

auto create(std::string_view package_name) -> Manifest;

auto write_manifest(const fs::Path &path, const Manifest &manifest)
    -> Result<void>;

auto update_manifest(const fs::Path &path, const Manifest &manifest)
    -> Result<void>;

auto validate(const fs::Path &path) -> bool;

} // namespace chassis::manifest

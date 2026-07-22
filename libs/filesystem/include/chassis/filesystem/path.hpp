#pragma once

#include <chassis/core/error/error.hpp>

#include <filesystem>

namespace chassis::fs {

using namespace chassis::error;
using path = std::filesystem::path;

auto current_path() -> Result<path>;
auto exists(const path &) -> bool;
auto canonical(const path &) -> Result<path>;
auto create_directory(const path &) -> Result<void>;
auto remove(const path &) -> Result<void>;

} // namespace chassis::fs

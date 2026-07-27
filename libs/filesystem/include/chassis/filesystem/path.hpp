#pragma once

#include <chassis/core/error/error.hpp>

#include <filesystem>

namespace chassis::fs {

using namespace chassis::error;
using path = std::filesystem::path;

auto current_path() -> Result<path>;
auto exists(const path &p) -> bool;
auto canonical(const path &p) -> Result<path>;
auto create_directory(const path &p) -> Result<void>;
auto remove(const path &p) -> Result<void>;

auto find_upward(const path &p, std::string_view search_term) -> Result<path>;

} // namespace chassis::fs

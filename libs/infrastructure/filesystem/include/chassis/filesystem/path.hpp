#pragma once

#include <chassis/core/error/error.hpp>

#include <filesystem>

namespace chassis::fs {

using namespace chassis::error;
using Path = std::filesystem::path;

[[nodiscard]]
auto current_path() -> Result<Path>;

[[nodiscard]]
auto exists(const Path &p) -> bool;

[[nodiscard]]
auto canonical(const Path &p) -> Result<Path>;

auto create_directory(const Path &p) -> Result<void>;
auto remove(const Path &p) -> Result<void>;

[[nodiscard]]
auto find_upward(const Path &p, std::string_view search_term) -> Result<Path>;

} // namespace chassis::fs

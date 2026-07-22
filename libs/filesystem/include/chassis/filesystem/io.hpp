#pragma once

#include <chassis/filesystem/path.hpp>

#include <string_view>
#include <vector>

namespace chassis::fs {

using namespace chassis::error;

auto read_text(const path &p) -> Result<std::string>;
auto write_text(const path &p, std::string_view text) -> Result<void>;

auto read_binary(const path &p) -> Result<std::vector<std::byte>>;

auto atomic_write(const path &p, std::string_view text) -> Result<void>;

} // namespace chassis::fs

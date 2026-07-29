#pragma once

#include <chassis/filesystem/path.hpp>

#include <string_view>
#include <vector>

namespace chassis::fs {

using namespace chassis::error;

using FileLines = std::vector<std::string>;
using FileLinesView = std::vector<std::string_view>;

auto read_from_file(const path &p) -> Result<FileLines>;
auto write_to_file(const path &p, FileLinesView text) -> Result<void>;
auto overwrite_file(const path &p, FileLinesView text) -> Result<void>;

// TODO
auto read_binary(const path &p) -> Result<std::vector<std::byte>>;

// TODO
auto atomic_write(const path &p, FileLinesView text) -> Result<void>;

} // namespace chassis::fs

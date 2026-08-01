#pragma once

#include <chassis/filesystem/path.hpp>
#include <chassis/filesystem/text_file.hpp>

namespace chassis::fs {

enum class FileWriteMode { Overwrite, Append };

[[nodiscard]]
auto read_text_file(const path &path) -> Result<TextFile>;

auto write_text_file(const path &path, const TextFile &file,
                     FileWriteMode mode = FileWriteMode::Overwrite)
    -> Result<void>;

auto exists(const path &path) -> bool;

auto copy_file(const path &from, const path &to) -> Result<void>;

auto remove_file(const path &path) -> Result<void>;

auto create_file(const path &path) -> Result<void>;

} // namespace chassis::fs

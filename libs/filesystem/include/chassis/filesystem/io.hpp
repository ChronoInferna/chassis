#pragma once

#include <chassis/filesystem/path.hpp>
#include <chassis/filesystem/text_file.hpp>

namespace chassis::fs {

enum class FileWriteMode { Overwrite, Append };

[[nodiscard]]
auto read_text_file(const Path &Path) -> Result<TextFile>;

auto write_text_file(const Path &Path, const TextFile &file,
                     FileWriteMode mode = FileWriteMode::Overwrite)
    -> Result<void>;

auto exists(const Path &Path) -> bool;

auto copy_file(const Path &from, const Path &to) -> Result<void>;

auto remove_file(const Path &Path) -> Result<void>;

auto create_file(const Path &Path) -> Result<void>;

} // namespace chassis::fs

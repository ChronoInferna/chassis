#pragma once

#include <chassis/core/file/file.hpp>
#include <chassis/filesystem/path.hpp>

#include <concepts>

namespace chassis::fs {

using namespace chassis::error;
using namespace chassis::file;

enum class FileWriteMode {
  Append,
  Overwrite,
};

template <typename F = File>
  requires std::derived_from<F, File>
auto read_file(const path &p) -> Result<F>;

template <typename F = File>
  requires std::derived_from<F, File>
auto write_file(const path &p, F input_file,
                FileWriteMode mode = FileWriteMode::Append) -> Result<void>;

// TODO
// auto atomic_write_file(const path &p, File input_file) -> Result<void>;

} // namespace chassis::fs

#pragma once

#include <chassis/core/error/error.hpp>
#include <chassis/filesystem/io.hpp>
#include <chassis/filesystem/path.hpp>
#include <chassis/filesystem/text_file.hpp>

#include <string_view>

namespace chassis::fs {

using namespace chassis::error;

// TODO other files necessary now?
class FileSystem {
public:
  virtual ~FileSystem() = default;

  [[nodiscard]] virtual auto exists(const Path &path) const -> bool = 0;
  [[nodiscard]] virtual auto current_path() const -> Result<Path> = 0;
  [[nodiscard]] virtual auto canonical(const Path &path) const
      -> Result<Path> = 0;
  virtual auto create_directory(const Path &path) -> Result<void> = 0;
  virtual auto remove(const Path &path) -> Result<void> = 0;
  [[nodiscard]] virtual auto find_upward(const Path &start,
                                         std::string_view search_term) const
      -> Result<Path> = 0;
  [[nodiscard]] virtual auto read_text_file(const Path &path) const
      -> Result<TextFile> = 0;
  virtual auto write_text_file(const Path &path, const TextFile &file,
                               FileWriteMode mode = FileWriteMode::Overwrite)
      -> Result<void> = 0;
};

} // namespace chassis::fs

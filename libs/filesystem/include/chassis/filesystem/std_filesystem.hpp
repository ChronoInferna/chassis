#pragma once

#include <chassis/filesystem/filesystem.hpp>

namespace chassis::fs {

class StdFileSystem : public FileSystem {
public:
  [[nodiscard]] auto exists(const Path &path) const -> bool override;
  [[nodiscard]] auto current_path() const -> Result<Path> override;
  [[nodiscard]] auto canonical(const Path &path) const -> Result<Path> override;
  auto create_directory(const Path &path) -> Result<void> override;
  auto remove(const Path &path) -> Result<void> override;
  [[nodiscard]] auto find_upward(const Path &start,
                                 std::string_view search_term) const
      -> Result<Path> override;
  [[nodiscard]] auto read_text_file(const Path &path) const
      -> Result<TextFile> override;
  auto write_text_file(const Path &path, const TextFile &file,
                       FileWriteMode mode = FileWriteMode::Overwrite)
      -> Result<void> override;
};

} // namespace chassis::fs

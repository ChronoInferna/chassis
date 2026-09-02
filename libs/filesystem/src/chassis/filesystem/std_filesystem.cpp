#include <chassis/filesystem/std_filesystem.hpp>

#include <chassis/filesystem/io.hpp>
#include <chassis/filesystem/path.hpp>

namespace chassis::fs {

auto StdFileSystem::exists(const Path &path) const -> bool {
  return chassis::fs::exists(path);
}

auto StdFileSystem::current_path() const -> Result<Path> {
  return chassis::fs::current_path();
}

auto StdFileSystem::canonical(const Path &path) const -> Result<Path> {
  return chassis::fs::canonical(path);
}

auto StdFileSystem::create_directory(const Path &path) -> Result<void> {
  return chassis::fs::create_directory(path);
}

auto StdFileSystem::remove(const Path &path) -> Result<void> {
  return chassis::fs::remove(path);
}

auto StdFileSystem::find_upward(const Path &start,
                                std::string_view search_term) const
    -> Result<Path> {
  return chassis::fs::find_upward(start, search_term);
}

auto StdFileSystem::read_text_file(const Path &path) const -> Result<TextFile> {
  return chassis::fs::read_text_file(path);
}

auto StdFileSystem::write_text_file(const Path &path, const TextFile &file,
                                    FileWriteMode mode) -> Result<void> {
  return chassis::fs::write_text_file(path, file, mode);
}

} // namespace chassis::fs

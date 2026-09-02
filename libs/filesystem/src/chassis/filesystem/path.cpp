#include <chassis/filesystem/path.hpp>

#include <chassis/core/error/error.hpp>

#include <exception>
#include <filesystem>
#include <string_view>

namespace chassis::fs {

using namespace chassis::error;

auto current_path() -> Result<Path> {
  Path res{};

  try {
    res = std::filesystem::current_path();
  } catch (const std::exception &) {
    return make_error(ErrorCode::FileSystemError);
  }

  return res;
}

auto exists(const Path &p) -> bool { return std::filesystem::exists(p); }

auto canonical(const Path &p) -> Result<Path> {
  Path res{};

  try {
    res = std::filesystem::canonical(p);
  } catch (const std::exception &) {
    return make_error(ErrorCode::FileSystemError);
  }

  return res;
}

auto create_directory(const Path &p) -> Result<void> {
  try {
    std::filesystem::create_directory(p);
  } catch (const std::exception &) {
    return make_error(ErrorCode::FileSystemError);
  }

  return {};
}

auto remove(const Path &p) -> Result<void> {
  try {
    std::filesystem::remove(p);
  } catch (const std::exception &) {
    return make_error(ErrorCode::FileSystemError);
  }

  return {};
}

auto find_upward(const Path &p, std::string_view search_term) -> Result<Path> {
  Path dir = p.empty() ? std::filesystem::current_path() : p;

  try {
    while (true) {
      if (dir.filename() == search_term && std::filesystem::exists(dir)) {
        return dir;
      }
      Path candidate = dir / search_term;
      if (std::filesystem::exists(candidate)) {
        return candidate;
      }
      if (!dir.has_parent_path() || dir.parent_path() == dir) {
        return make_error(ErrorCode::MissingFile);
      }
      dir = dir.parent_path();
    }
  } catch (const std::exception &) {
    return make_error(ErrorCode::FileSystemError);
  }
}

} // namespace chassis::fs

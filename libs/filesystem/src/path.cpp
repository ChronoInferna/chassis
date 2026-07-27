#include <chassis/filesystem/path.hpp>

#include <chassis/core/error/error.hpp>

#include <exception>
#include <filesystem>
#include <string_view>

namespace chassis::fs {

using namespace chassis::error;

auto current_path() -> Result<path> {
  path res{};

  try {
    res = std::filesystem::current_path();
  } catch (const std::exception &) {
    return make_error(ErrorCode::FileSystemError);
  }

  return res;
}

auto exists(const path &p) -> bool { return std::filesystem::exists(p); }

auto canonical(const path &p) -> Result<path> {
  path res{};

  try {
    res = std::filesystem::canonical(p);
  } catch (const std::exception &) {
    return make_error(ErrorCode::FileSystemError);
  }

  return res;
}

auto create_directory(const path &p) -> Result<void> {
  try {
    std::filesystem::create_directory(p);
  } catch (const std::exception &) {
    return make_error(ErrorCode::FileSystemError);
  }

  return {};
}

auto remove(const path &p) -> Result<void> {
  try {
    std::filesystem::remove(p);
  } catch (const std::exception &) {
    return make_error(ErrorCode::FileSystemError);
  }

  return {};
}

auto find_upward(const path &p, std::string_view search_term) -> Result<path> {
  path res = p.empty() ? std::filesystem::current_path() : p;

  try {
    while (res.filename() != search_term) {
      if (!res.has_parent_path() || res.parent_path() == res) {
        return make_error(ErrorCode::MissingFile);
      }

      res = res.parent_path();
    }

    return res;
  } catch (const std::exception &) {
    return make_error(ErrorCode::ProcessError);
  }

  return res;
}

} // namespace chassis::fs

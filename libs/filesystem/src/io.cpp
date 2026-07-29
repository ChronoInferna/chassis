#include <chassis/filesystem/io.hpp>

#include <chassis/core/error/error.hpp>

#include <fstream>
#include <string>

namespace chassis::fs {

using namespace chassis::error;

auto read_from_file(const path &p) -> Result<FileLines> {
  std::ifstream file{p};
  if (!file.is_open()) {
    return make_error(ErrorCode::InvalidArgument);
  }

  FileLines res{};
  std::string buffer;
  while (std::getline(file, buffer)) {
    res.emplace_back(buffer);
  }

  return res;
}

auto write_to_file(const path &p, FileLinesView text) -> Result<void> {
  std::ofstream file{p, std::ios::app};
  if (!file.is_open()) {
    return make_error(ErrorCode::InvalidArgument);
  }

  for (const auto &line : text) {
    file << line << "\n";
  }

  file.close();
  return {};
}

auto overwrite_file(const path &p, FileLinesView text) -> Result<void> {
  std::ofstream file{p};
  if (!file.is_open()) {
    return make_error(ErrorCode::InvalidArgument);
  }

  for (const auto &line : text) {
    file << line << "\n";
  }

  file.close();
  return {};
}

// TODO
// auto read_binary(const path &p) -> Result<std::vector<std::byte>> {}

// TODO
// auto atomic_write(const path &p, FileLinesView text) ->
// Result<void> {}

} // namespace chassis::fs

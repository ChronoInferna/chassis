#include <chassis/filesystem/io.hpp>

#include <chassis/core/error/error.hpp>

#include <fstream>
#include <string>

namespace chassis::fs {

using namespace chassis::error;
using namespace chassis::file;

auto read_file(const path &p) -> Result<File> {
  std::ifstream file{p};
  if (!file.is_open()) {
    return make_error(ErrorCode::InvalidArgument);
  }

  File res{};
  std::string buffer;
  while (std::getline(file, buffer)) {
    // TODO
  }

  return res;
}

auto append_file(const path &p, File input_input) -> Result<void> {
  std::ofstream file{p, std::ios::app};
  if (!file.is_open()) {
    return make_error(ErrorCode::InvalidArgument);
  }

  // TODO
  // for (const auto &line : text) {
  //   file << line << "\n";
  // }

  file.close();
  return {};
}

auto overwrite_file(const path &p, File input_file) -> Result<void> {
  std::ofstream file{p};
  if (!file.is_open()) {
    return make_error(ErrorCode::InvalidArgument);
  }

  // TODO
  // for (const auto &line : input_file) {
  //   file << line << "\n";
  // }

  file.close();
  return {};
}

// TODO
// auto read_binary_file(const path &p) -> Result<File> {}

// TODO
// auto atomic_write_file(const path &p, File input_file) ->
// Result<void> {}

} // namespace chassis::fs

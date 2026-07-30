#pragma once

#include <chassis/core/file/file.hpp>
#include <chassis/filesystem/path.hpp>

#include <concepts>
#include <fstream>

namespace chassis::fs {

using namespace chassis::error;
using namespace chassis::file;

enum class FileWriteMode {
  Append,
  Overwrite,
};

template <typename F = File>
  requires(std::derived_from<F, File> && !is_binary_file<F>)
auto read_file(const path &p) -> Result<F> {
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

template <typename F = File>
  requires(std::derived_from<F, File> && !is_binary_file<F>)
auto write_file(const path &p, F input_file,
                FileWriteMode mode = FileWriteMode::Append) -> Result<void> {
  std::ofstream file;

  if (mode == FileWriteMode::Append) {
    file.open(p, std::ios::app);
  } else if (mode == FileWriteMode::Overwrite) {
    file.open(p, std::ios::trunc);
  } else {
    return make_error(ErrorCode::InvalidArgument);
  }

  if (!file.is_open()) {
    return make_error(ErrorCode::InvalidArgument);
  }

  // TODO
  // for (const auto &line : input_file.content()) {
  //   file << line << "\n";
  // }

  file.close();
  return {};
}

// TODO
// template <typename F = File>
//   requires (std::derived_from<F, File> && is_binary_file<F>)
//   auto write_binary_file();

// TODO
// auto atomic_write_file(const path &p, File input_file) -> Result<void>;

} // namespace chassis::fs

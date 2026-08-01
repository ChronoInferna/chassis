#include <chassis/filesystem/io.hpp>

#include <chassis/core/error/error.hpp>

#include <fstream>

namespace chassis::fs {

auto read_text_file(const path &path) -> Result<TextFile> {
  std::ifstream file{path};

  if (!file.is_open()) {
    return make_error(ErrorCode::InvalidArgument);
  }

  std::vector<std::string> lines;
  std::string buffer;

  while (std::getline(file, buffer)) {
    lines.push_back(std::move(buffer));
  }

  if (file.bad()) {
    return make_error(ErrorCode::Unknown);
  }

  return TextFile{std::move(lines)};
}

auto write_text_file(const path &path, const TextFile &file, FileWriteMode mode)
    -> Result<void> {
  std::ios_base::openmode open_mode = std::ios::out;

  switch (mode) {
  case FileWriteMode::Overwrite:
    open_mode |= std::ios::trunc;
    break;

  case FileWriteMode::Append:
    open_mode |= std::ios::app;
    break;
  }

  std::ofstream output{path, open_mode};

  if (!output.is_open()) {
    return make_error(ErrorCode::InvalidArgument);
  }

  for (const auto &line : file.lines()) {
    output << line << '\n';
  }

  if (!output) {
    return make_error(ErrorCode::Unknown);
  }

  return {};
}
}

// TODO
// auto exists(const path &path) -> bool;

// auto copy_file(const path &from, const path &to) -> Result<void>;

// auto remove_file(const path &path) -> Result<void>;

// auto create_file(const path &path) -> Result<void>;

} // namespace chassis::fs

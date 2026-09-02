#include <chassis/filesystem/text_file.hpp>

#include <chassis/core/error/error.hpp>

#include <string>

namespace chassis::fs {

using namespace chassis::error;

TextFile::TextFile(std::vector<std::string> lines) : lines_(std::move(lines)) {}

auto TextFile::lines() const noexcept -> std::span<const std::string> {
  return lines_;
}

auto TextFile::lines() noexcept -> std::span<std::string> { return lines_; }

auto TextFile::line(std::size_t index) const -> Result<const std::string &> {
  if (index >= lines_.size()) {
    return make_error(ErrorCode::InvalidArgument);
  }

  return lines_[index];
}

auto TextFile::line(std::size_t index) -> Result<std::string &> {
  if (index >= lines_.size()) {
    return make_error(ErrorCode::InvalidArgument);
  }

  return lines_[index];
}

auto TextFile::set_lines(std::vector<std::string> lines) -> void {
  lines_ = std::move(lines);
}

auto TextFile::text() const -> std::string {
  if (lines_.empty()) {
    return {};
  }

  std::size_t total_size = lines_.size() - 1;

  for (const auto &line : lines_) {
    total_size += line.size();
  }

  std::string result;
  result.reserve(total_size);

  for (std::size_t i = 0; i < lines_.size(); ++i) {
    result += lines_[i];

    if (i + 1 != lines_.size()) {
      result += '\n';
    }
  }

  return result;
}

auto TextFile::clear() -> void { lines_.clear(); }

} // namespace chassis::fs

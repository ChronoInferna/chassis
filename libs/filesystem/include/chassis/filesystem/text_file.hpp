#pragma once

#include <chassis/core/error/error.hpp>

#include <span>
#include <string>
#include <vector>

namespace chassis::fs {

using namespace chassis::error;

class TextFile {
public:
  TextFile() = default;
  explicit TextFile(std::vector<std::string> lines);

  [[nodiscard]]
  auto lines() const noexcept -> std::span<const std::string>;

  [[nodiscard]]
  auto lines() noexcept -> std::span<std::string>;

  [[nodiscard]]
  auto line(std::size_t index) const -> Result<const std::string &>;

  [[nodiscard]]
  auto line(std::size_t index) -> Result<std::string &>;

  auto set_lines(std::vector<std::string> lines) -> void;

  [[nodiscard]]
  auto text() const -> std::string;

  auto clear() -> void;

private:
  std::vector<std::string> lines_;
};

} // namespace chassis::fs

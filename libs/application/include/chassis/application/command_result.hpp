#pragma once

#include <chassis/core/error/error.hpp>

#include <optional>
#include <string>

namespace chassis::application {

struct CommandResult {
  bool success = false;
  std::string message;
  std::optional<error::Error> error;
};

} // namespace chassis::application

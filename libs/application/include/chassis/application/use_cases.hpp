#pragma once

#include <chassis/core/error/error.hpp>
#include <chassis/filesystem/path.hpp>

#include <optional>
#include <string>

namespace chassis::application {

struct CommandResult {
  bool success = false;
  std::string message;
  std::optional<error::Error> error;
};

[[nodiscard]]
auto init_project(const fs::Path &path) -> CommandResult;

[[nodiscard]]
auto new_project(const fs::Path &path, const std::string &project_name)
    -> CommandResult;

[[nodiscard]]
auto build_project(const fs::Path &path) -> CommandResult;

} // namespace chassis::application

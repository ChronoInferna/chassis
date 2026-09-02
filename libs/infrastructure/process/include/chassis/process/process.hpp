#pragma once

#include <chassis/core/error/error.hpp>
#include <chassis/filesystem/path.hpp>

#include <vector>

namespace chassis::process {

struct Command {
  fs::Path program;
  std::vector<std::string> arguments;
};

struct Output {
  int exit_code;

  auto succeeded() const noexcept -> bool { return exit_code == 0; }
};

auto run(const Command &command) -> error::Result<Output>;

} // namespace chassis::process

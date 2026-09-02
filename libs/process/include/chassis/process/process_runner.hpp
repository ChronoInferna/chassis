#pragma once

#include <chassis/core/error/error.hpp>
#include <chassis/filesystem/path.hpp>

#include <string>
#include <vector>

namespace chassis::process {

using namespace chassis::error;

struct Command {
  fs::Path program;
  std::vector<std::string> arguments;
  fs::Path working_directory = {};
};

struct Output {
  int exit_code = 0;

  [[nodiscard]] auto succeeded() const noexcept -> bool {
    return exit_code == 0;
  }
};

class ProcessRunner {
public:
  virtual ~ProcessRunner() = default;

  virtual auto run(const Command &command) -> Result<Output> = 0;
};

} // namespace chassis::process

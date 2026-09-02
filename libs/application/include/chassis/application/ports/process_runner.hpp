#pragma once

#include <chassis/core/error/error.hpp>
#include <chassis/filesystem/path.hpp>

#include <string>
#include <vector>

namespace chassis::application::ports {

struct ProcessCommand {
  fs::Path program;
  std::vector<std::string> arguments;
};

struct ProcessOutput {
  int exit_code = 0;

  [[nodiscard]] auto succeeded() const noexcept -> bool { return exit_code == 0; }
};

class ProcessRunner {
public:
  virtual ~ProcessRunner() = default;

  [[nodiscard]] virtual auto run(const ProcessCommand &command) const
      -> error::Result<ProcessOutput> = 0;
};

} // namespace chassis::application::ports

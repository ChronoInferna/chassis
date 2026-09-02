#pragma once

#include <chassis/application/ports/process_runner.hpp>

namespace chassis::infrastructure::process {

class PosixProcessRunner final : public application::ports::ProcessRunner {
public:
  [[nodiscard]] auto run(const application::ports::ProcessCommand &command) const
      -> error::Result<application::ports::ProcessOutput> override;
};

} // namespace chassis::infrastructure::process

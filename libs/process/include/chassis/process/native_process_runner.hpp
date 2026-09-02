#pragma once

#include <chassis/process/process_runner.hpp>

namespace chassis::process {

class NativeProcessRunner : public ProcessRunner {
public:
  auto run(const Command &command) -> Result<Output> override;
};

} // namespace chassis::process

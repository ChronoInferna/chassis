#include <chassis/process/process.hpp>

namespace chassis::process {

auto run(const Command &command) -> Result<Output> {
  NativeProcessRunner runner;
  return runner.run(command);
}

} // namespace chassis::process

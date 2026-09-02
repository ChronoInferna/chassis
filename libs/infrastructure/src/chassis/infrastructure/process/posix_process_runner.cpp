#include <chassis/infrastructure/process/posix_process_runner.hpp>

#include <chassis/process/process.hpp>

namespace chassis::infrastructure::process {

auto PosixProcessRunner::run(
    const application::ports::ProcessCommand &command) const
    -> error::Result<application::ports::ProcessOutput> {
  chassis::process::Command process_command = {
      .program = command.program,
      .arguments = command.arguments,
  };

  CHASSIS_TRY_VALUE(output, chassis::process::run(process_command));

  return application::ports::ProcessOutput{.exit_code = output.exit_code};
}

} // namespace chassis::infrastructure::process

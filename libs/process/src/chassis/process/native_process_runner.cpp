#include <chassis/process/native_process_runner.hpp>

#include <chassis/core/error/error.hpp>

#include <sys/wait.h>
#include <unistd.h>

namespace chassis::process {

using namespace chassis::error;

namespace {

auto execute_command(const Command &command) -> void {
  if (!command.working_directory.empty()) {
    if (chdir(command.working_directory.c_str()) != 0) {
      _exit(127);
    }
  }

  std::vector<char *> argv;
  argv.reserve(command.arguments.size() + 2);

  argv.push_back(const_cast<char *>(command.program.c_str()));

  for (const auto &argument : command.arguments) {
    argv.push_back(const_cast<char *>(argument.c_str()));
  }

  argv.push_back(nullptr);

  execvp(command.program.c_str(), argv.data());

  // Only reached if execvp() failed.
  _exit(127);
}

} // namespace

auto NativeProcessRunner::run(const Command &command) -> Result<Output> {
  pid_t pid = fork();

  if (pid == -1) {
    return make_error(ErrorCode::ProcessError);
  }

  if (pid == 0) {
    execute_command(command);
  }

  int status = 0;

  if (waitpid(pid, &status, 0) == -1) {
    return make_error(ErrorCode::ProcessError);
  }

  if (WIFEXITED(status)) {
    return Output{.exit_code = WEXITSTATUS(status)};
  }

  if (WIFSIGNALED(status)) {
    return Output{.exit_code = 128 + WTERMSIG(status)};
  }

  return make_error(ErrorCode::ProcessError);
}

} // namespace chassis::process

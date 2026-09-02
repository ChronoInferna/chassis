#pragma once

#include "application/build_service.hpp"
#include "application/project_service.hpp"
#include <chassis/core/error/error.hpp>
#include <chassis/process/process_runner.hpp>

namespace chassis::app {

using namespace chassis::error;

struct RunOptions {
  fs::Path path = std::filesystem::current_path();
  std::string preset = "default";
  std::vector<std::string> args;
};

struct RunResult {
  builder::BuildResult build_result;
  process::Output run_output;
};

class RunService {
public:
  RunService(ProjectService &project_service, BuildService &build_service,
             process::ProcessRunner &process_runner)
      : project_service_(project_service), build_service_(build_service),
        process_runner_(process_runner) {}

  auto run(const RunOptions &options) -> Result<RunResult>;

private:
  ProjectService &project_service_;
  BuildService &build_service_;
  process::ProcessRunner &process_runner_;
};

} // namespace chassis::app

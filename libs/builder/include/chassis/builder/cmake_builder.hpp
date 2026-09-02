#pragma once

#include <chassis/builder/builder.hpp>
#include <chassis/process/process_runner.hpp>

namespace chassis::builder {

class CMakeBuilder : public Builder {
public:
  CMakeBuilder() = default;
  explicit CMakeBuilder(process::ProcessRunner &runner) : runner_(&runner) {}

  auto build(const manifest::Project &project, const BuildOptions &options = {})
      -> Result<BuildResult> override;

private:
  std::unique_ptr<process::ProcessRunner> runner_ = nullptr;
};

} // namespace chassis::builder

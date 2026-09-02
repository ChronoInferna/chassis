#pragma once

#include <chassis/core/error/error.hpp>
#include <chassis/manifest/project.hpp>
#include <chassis/process/process_runner.hpp>
#include <string>

namespace chassis::builder {

using namespace chassis::error;

struct BuildOptions {
  std::string preset = "default";
};

struct BuildResult {
  process::Output output;
};

class Builder {
public:
  virtual ~Builder() = default;

  virtual auto build(const manifest::Project &project,
                     const BuildOptions &options = {})
      -> Result<BuildResult> = 0;
};

} // namespace chassis::builder

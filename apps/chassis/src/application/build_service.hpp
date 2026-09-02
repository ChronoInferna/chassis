#pragma once

#include "application/project_service.hpp"
#include <chassis/builder/builder.hpp>
#include <chassis/core/error/error.hpp>

namespace chassis::app {

using namespace chassis::error;

class BuildService {
public:
  BuildService(ProjectService &project_service, builder::Builder &builder)
      : project_service_(project_service), builder_(builder) {}

  auto build(const fs::Path &path, const builder::BuildOptions &options = {})
      -> Result<builder::BuildResult>;

  auto build(const manifest::Project &project,
             const builder::BuildOptions &options = {})
      -> Result<builder::BuildResult>;

private:
  ProjectService &project_service_;
  builder::Builder &builder_;
};

} // namespace chassis::app

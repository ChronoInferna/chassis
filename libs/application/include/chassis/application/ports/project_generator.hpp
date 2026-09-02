#pragma once

#include <chassis/core/error/error.hpp>
#include <chassis/domain/project/project_rules.hpp>

namespace chassis::application::ports {

class ProjectGenerator {
public:
  virtual ~ProjectGenerator() = default;

  virtual auto generate(const domain::project::ProjectSpec &project)
      -> error::Result<void> = 0;
};

} // namespace chassis::application::ports

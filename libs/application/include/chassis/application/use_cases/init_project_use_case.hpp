#pragma once

#include <chassis/application/command_result.hpp>
#include <chassis/application/ports/project_generator.hpp>
#include <chassis/filesystem/path.hpp>

namespace chassis::application {

class InitProjectUseCase {
public:
  explicit InitProjectUseCase(ports::ProjectGenerator &project_generator)
      : project_generator_(project_generator) {}

  [[nodiscard]] auto run(const fs::Path &path) const -> CommandResult;

private:
  ports::ProjectGenerator &project_generator_;
};

} // namespace chassis::application

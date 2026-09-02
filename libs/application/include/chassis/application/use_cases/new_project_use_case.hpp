#pragma once

#include <chassis/application/command_result.hpp>
#include <chassis/application/ports/project_generator.hpp>
#include <chassis/filesystem/path.hpp>

#include <string>

namespace chassis::application {

class NewProjectUseCase {
public:
  explicit NewProjectUseCase(ports::ProjectGenerator &project_generator)
      : project_generator_(project_generator) {}

  [[nodiscard]] auto run(const fs::Path &path, const std::string &project_name)
      const -> CommandResult;

private:
  ports::ProjectGenerator &project_generator_;
};

} // namespace chassis::application

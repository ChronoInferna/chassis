#include <chassis/application/use_cases/new_project_use_case.hpp>

#include <chassis/domain/project/project_rules.hpp>

namespace chassis::application {

auto NewProjectUseCase::run(const fs::Path &path,
                            const std::string &project_name) const
    -> CommandResult {
  auto project_spec = domain::project::resolve_new_project(path, project_name);
  if (!project_spec) {
    return {.success = false,
            .message = "Failed to create project",
            .error = project_spec.error()};
  }

  auto generate_result = project_generator_.generate(*project_spec);
  if (!generate_result) {
    return {.success = false,
            .message = "Failed to create project",
            .error = generate_result.error()};
  }

  return {.success = true,
          .message =
              "Project successfully created at: " +
              project_spec->manifest_path.string()};
}

} // namespace chassis::application

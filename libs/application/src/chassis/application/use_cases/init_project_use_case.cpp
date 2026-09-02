#include <chassis/application/use_cases/init_project_use_case.hpp>

#include <chassis/domain/project/project_rules.hpp>

namespace chassis::application {

auto InitProjectUseCase::run(const fs::Path &path) const -> CommandResult {
  auto project_spec = domain::project::resolve_init_project(path);
  if (!project_spec) {
    return {.success = false,
            .message = "Failed to initialize project",
            .error = project_spec.error()};
  }

  auto generate_result = project_generator_.generate(*project_spec);
  if (!generate_result) {
    return {.success = false,
            .message = "Failed to initialize project",
            .error = generate_result.error()};
  }

  return {.success = true,
          .message =
              "Project successfully initialized at: " +
              project_spec->manifest_path.string()};
}

} // namespace chassis::application

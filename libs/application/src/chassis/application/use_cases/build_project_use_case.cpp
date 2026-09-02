#include <chassis/application/use_cases/build_project_use_case.hpp>

namespace chassis::application {

auto BuildProjectUseCase::run(const fs::Path &path) const -> CommandResult {
  auto manifest_path = path / "Chassis.toml";

  if (!manifest_store_.exists(manifest_path)) {
    return {.success = false,
            .message = "Manifest file does not exist at path: " +
                       manifest_path.string()};
  }

  auto validate_result = manifest_store_.validate(manifest_path);
  if (!validate_result) {
    return {.success = false,
            .message = "Manifest validation failed",
            .error = validate_result.error()};
  }

  auto manifest_result = manifest_store_.read(manifest_path);
  if (!manifest_result) {
    return {.success = false,
            .message = "Failed to read manifest file",
            .error = manifest_result.error()};
  }

  ports::ProcessCommand cmake_command = {
      .program = "cmake",
      .arguments = {"--workflow", "--preset", "debug"},
  };

  auto run_result = process_runner_.run(cmake_command);
  if (!run_result) {
    return {.success = false,
            .message = "Failed to run cmake",
            .error = run_result.error()};
  }

  if (!run_result->succeeded()) {
    return {.success = false,
            .message = "Build failed with exit code: " +
                       std::to_string(run_result->exit_code)};
  }

  return {.success = true,
          .message = "Build completed with exit code: " +
                     std::to_string(run_result->exit_code)};
}

} // namespace chassis::application

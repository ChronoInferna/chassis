#include <chassis/application/use_cases.hpp>

#include <chassis/filesystem/path.hpp>
#include <chassis/manifest/manifest.hpp>
#include <chassis/process/process.hpp>

namespace chassis::application {

namespace {
constexpr auto kManifestName = "Chassis.toml";

auto make_error_result(std::string message, const error::Error &err)
    -> CommandResult {
  return {.success = false, .message = std::move(message), .error = err};
}

} // namespace

auto init_project(const fs::Path &path) -> CommandResult {
  auto manifest_path = path / kManifestName;

  if (fs::exists(manifest_path)) {
    return {.success = false,
            .message = "Manifest file already exists at: " +
                       manifest_path.string()};
  }

  auto manifest = manifest::create(path.filename().native());
  auto write_res = manifest::write_manifest(manifest_path, manifest);
  if (!write_res) {
    return make_error_result("Failed to create manifest file", write_res.error());
  }

  return {.success = true,
          .message = "Project successfully initialized at: " +
                     manifest_path.string()};
}

auto new_project(const fs::Path &path, const std::string &project_name)
    -> CommandResult {
  if (project_name.empty()) {
    return {.success = false, .message = "Project name cannot be empty"};
  }

  auto project_path = path / project_name;
  auto manifest_path = project_path / kManifestName;

  if (fs::exists(manifest_path)) {
    return {.success = false,
            .message = "Manifest file already exists at: " +
                       manifest_path.string()};
  }

  if (!fs::exists(project_path)) {
    auto create_res = fs::create_directory(project_path);
    if (!create_res) {
      return make_error_result("Failed to create project directory",
                               create_res.error());
    }
  }

  auto manifest = manifest::create(project_path.filename().native());
  auto write_res = manifest::write_manifest(manifest_path, manifest);
  if (!write_res) {
    return make_error_result("Failed to create manifest file", write_res.error());
  }

  return {.success = true,
          .message = "Project successfully created at: " +
                     manifest_path.string()};
}

auto build_project(const fs::Path &path) -> CommandResult {
  auto manifest_path = path / kManifestName;

  if (!fs::exists(manifest_path)) {
    return {.success = false,
            .message = "Manifest file does not exist at path: " +
                       manifest_path.string()};
  }

  auto validate_res = manifest::validate(manifest_path);
  if (!validate_res) {
    return make_error_result("Manifest validation failed", validate_res.error());
  }

  auto read_res = manifest::read_manifest(manifest_path);
  if (!read_res) {
    return make_error_result("Failed to read manifest file", read_res.error());
  }

  process::Command cmake = {
      .program = "cmake",
      .arguments = {"--workflow", "--preset", "debug"},
  };
  auto run_res = process::run(cmake);

  if (!run_res) {
    return make_error_result("Failed to run cmake", run_res.error());
  }

  if (!run_res->succeeded()) {
    return {.success = false,
            .message =
                "Build failed with exit code: " + std::to_string(run_res->exit_code)};
  }

  return {.success = true,
          .message = "Build completed with exit code: " +
                     std::to_string(run_res->exit_code)};
}

} // namespace chassis::application

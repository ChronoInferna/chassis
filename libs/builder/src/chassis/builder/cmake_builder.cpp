#include <chassis/builder/cmake_builder.hpp>
#include <chassis/process/native_process_runner.hpp>

namespace chassis::builder {

auto CMakeBuilder::build(const manifest::Project &project,
                         const BuildOptions &options) -> Result<BuildResult> {
  std::string preset = options.preset.empty() ? "default" : options.preset;

  process::Command cmd = {
      .program = "cmake",
      .arguments = {"--workflow", "--preset", preset},
      .working_directory = project.path,
  };

  if (runner_) {
    CHASSIS_TRY_VALUE(out, runner_->run(cmd));
    return BuildResult{.output = out};
  }

  process::NativeProcessRunner default_runner;
  CHASSIS_TRY_VALUE(out, default_runner.run(cmd));
  return BuildResult{.output = out};
}

} // namespace chassis::builder

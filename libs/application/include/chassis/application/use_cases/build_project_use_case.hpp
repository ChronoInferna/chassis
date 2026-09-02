#pragma once

#include <chassis/application/command_result.hpp>
#include <chassis/application/ports/manifest_store.hpp>
#include <chassis/application/ports/process_runner.hpp>
#include <chassis/filesystem/path.hpp>

namespace chassis::application {

class BuildProjectUseCase {
public:
  BuildProjectUseCase(ports::ManifestStore &manifest_store,
                      ports::ProcessRunner &process_runner)
      : manifest_store_(manifest_store), process_runner_(process_runner) {}

  [[nodiscard]] auto run(const fs::Path &path) const -> CommandResult;

private:
  ports::ManifestStore &manifest_store_;
  ports::ProcessRunner &process_runner_;
};

} // namespace chassis::application

#pragma once

#include <chassis/application/ports/project_generator.hpp>
#include <chassis/application/ports/manifest_store.hpp>

namespace chassis::infrastructure::project {

class BasicProjectGenerator final : public application::ports::ProjectGenerator {
public:
  explicit BasicProjectGenerator(application::ports::ManifestStore &manifest_store)
      : manifest_store_(manifest_store) {}

  auto generate(const domain::project::ProjectSpec &project)
      -> error::Result<void> override;

private:
  application::ports::ManifestStore &manifest_store_;
};

} // namespace chassis::infrastructure::project

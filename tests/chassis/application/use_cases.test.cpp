#include <chassis/application/ports/manifest_store.hpp>
#include <chassis/application/ports/process_runner.hpp>
#include <chassis/application/ports/project_generator.hpp>
#include <chassis/application/use_cases/build_project_use_case.hpp>
#include <chassis/application/use_cases/init_project_use_case.hpp>
#include <chassis/application/use_cases/new_project_use_case.hpp>

#include <gtest/gtest.h>

namespace {

class FakeProjectGenerator final : public chassis::application::ports::ProjectGenerator {
public:
  auto generate(const chassis::domain::project::ProjectSpec &project)
      -> chassis::error::Result<void> override {
    last_project = project;
    called = true;
    return result;
  }

  bool called = false;
  chassis::error::Result<void> result = {};
  chassis::domain::project::ProjectSpec last_project{};
};

class FakeManifestStore final : public chassis::application::ports::ManifestStore {
public:
  [[nodiscard]] auto exists(const chassis::fs::Path &) const -> bool override {
    return manifest_exists;
  }

  [[nodiscard]] auto create_default(std::string_view package_name) const
      -> chassis::manifest::Manifest override {
    return chassis::manifest::create(package_name);
  }

  auto write(const chassis::fs::Path &, const chassis::manifest::Manifest &)
      -> chassis::error::Result<void> override {
    return {};
  }

  [[nodiscard]] auto read(const chassis::fs::Path &) const
      -> chassis::error::Result<chassis::manifest::Manifest> override {
    return chassis::manifest::Manifest{};
  }

  [[nodiscard]] auto validate(const chassis::fs::Path &) const
      -> chassis::error::Result<void> override {
    return validate_result;
  }

  bool manifest_exists = true;
  chassis::error::Result<void> validate_result = {};
};

class FakeProcessRunner final : public chassis::application::ports::ProcessRunner {
public:
  [[nodiscard]] auto run(const chassis::application::ports::ProcessCommand &)
      const -> chassis::error::Result<chassis::application::ports::ProcessOutput>
      override {
    return output;
  }

  chassis::error::Result<chassis::application::ports::ProcessOutput> output =
      chassis::application::ports::ProcessOutput{.exit_code = 0};
};

TEST(ApplicationUseCases, InitProjectUseCaseDelegatesGeneration) {
  FakeProjectGenerator project_generator{};
  chassis::application::InitProjectUseCase use_case{project_generator};

  auto result = use_case.run("/tmp/myapp");

  EXPECT_TRUE(result.success);
  EXPECT_TRUE(project_generator.called);
}

TEST(ApplicationUseCases, NewProjectUseCaseRequiresName) {
  FakeProjectGenerator project_generator{};
  chassis::application::NewProjectUseCase use_case{project_generator};

  auto result = use_case.run("/tmp", "");

  EXPECT_FALSE(result.success);
  EXPECT_TRUE(result.error.has_value());
}

TEST(ApplicationUseCases, BuildProjectUseCaseChecksManifestPresence) {
  FakeManifestStore manifest_store{};
  manifest_store.manifest_exists = false;
  FakeProcessRunner process_runner{};

  chassis::application::BuildProjectUseCase use_case{manifest_store,
                                                     process_runner};

  auto result = use_case.run("/tmp");

  EXPECT_FALSE(result.success);
}

TEST(ApplicationUseCases, BuildProjectUseCaseFailsOnProcessExitCode) {
  FakeManifestStore manifest_store{};
  FakeProcessRunner process_runner{};
  process_runner.output =
      chassis::application::ports::ProcessOutput{.exit_code = 1};

  chassis::application::BuildProjectUseCase use_case{manifest_store,
                                                     process_runner};

  auto result = use_case.run("/tmp");

  EXPECT_FALSE(result.success);
}

} // namespace

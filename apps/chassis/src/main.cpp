#include <CLI/CLI.hpp>

#include "application/build_service.hpp"
#include "application/init_service.hpp"
#include "application/project_service.hpp"
#include "application/run_service.hpp"
#include "infrastructure/cli/cli.hpp"
#include "infrastructure/logging/logger.hpp"

#include <chassis/builder/cmake_builder.hpp>
#include <chassis/filesystem/std_filesystem.hpp>
#include <chassis/manifest/toml_manifest_store.hpp>
#include <chassis/process/native_process_runner.hpp>

int main(int argc, char **argv) {
  CLI::App app{"Chassis - C++ Project Management Tool"};
  argv = app.ensure_utf8(argv);

  chassis::infra::logging::init_logging();

  // TODO move creation of services and whatnot to another file

  // Infrastructure Ports & Adapters
  chassis::fs::StdFileSystem file_system;
  chassis::manifest::TomlManifestStore manifest_store(file_system);
  chassis::process::NativeProcessRunner process_runner;
  chassis::builder::CMakeBuilder cmake_builder(process_runner);

  // Application Services
  chassis::app::ProjectService project_service(file_system, manifest_store);
  chassis::app::InitService init_service(file_system, manifest_store);
  chassis::app::BuildService build_service(project_service, cmake_builder);
  chassis::app::RunService run_service(project_service, build_service,
                                       process_runner);

  // CLI Presentation & Dispatch
  chassis::infra::cli::setup_cli(app, init_service, build_service, run_service);

  CLI11_PARSE(app, argc, argv);
  return 0;
}

#pragma once

#include <chassis/application/command_result.hpp>
#include <chassis/application/use_cases/build_project_use_case.hpp>
#include <chassis/application/use_cases/init_project_use_case.hpp>
#include <chassis/application/use_cases/new_project_use_case.hpp>
#include <chassis/infrastructure/manifest/toml_manifest_store.hpp>
#include <chassis/infrastructure/process/posix_process_runner.hpp>
#include <chassis/infrastructure/project/basic_project_generator.hpp>

#include <CLI/CLI.hpp>

#include <array>
#include <span>
#include <string_view>

struct CommandContext {
  chassis::infrastructure::manifest::TomlManifestStore manifest_store;
  chassis::infrastructure::process::PosixProcessRunner process_runner;
  chassis::infrastructure::project::BasicProjectGenerator project_generator;

  chassis::application::InitProjectUseCase init_use_case;
  chassis::application::NewProjectUseCase new_use_case;
  chassis::application::BuildProjectUseCase build_use_case;

  CommandContext();
};

using CommandRegistrar = void (*)(CLI::App &app, CommandContext &context);

struct CommandModule {
  std::string_view name;
  std::string_view description;
  CommandRegistrar register_command;
};

auto render_command_result(const chassis::application::CommandResult &result)
    -> void;

auto command_modules() -> std::span<const CommandModule>;

auto register_all_commands(CLI::App &app) -> void;

#pragma once

#include <filesystem>

#include <CLI/CLI.hpp>

struct CommandContext;

struct BuildOptions {
  std::filesystem::path path = std::filesystem::current_path();
};

auto add_build_command(CLI::App &app, CommandContext &context) -> void;

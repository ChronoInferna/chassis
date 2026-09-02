#pragma once

#include <filesystem>

#include <CLI/CLI.hpp>

struct CommandContext;

struct InitOptions {
  std::filesystem::path path = std::filesystem::current_path();
};

auto add_init_command(CLI::App &app, CommandContext &context) -> void;

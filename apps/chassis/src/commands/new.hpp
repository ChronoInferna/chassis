#pragma once

#include <filesystem>
#include <string>

#include <CLI/CLI.hpp>

struct CommandContext;

struct NewOptions {
  std::filesystem::path path = std::filesystem::current_path();
  std::string project_name;
};

auto add_new_command(CLI::App &app, CommandContext &context) -> void;

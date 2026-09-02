#pragma once

#include <filesystem>

#include <CLI/CLI.hpp>

struct InitOptions {
  std::filesystem::path path = std::filesystem::current_path();
};

auto add_init_command(CLI::App &app) -> void;

auto run_init_command(const InitOptions &options) -> void;

#pragma once

#include <filesystem>

#include <CLI/CLI.hpp>

struct BuildOptions {
  std::filesystem::path path = std::filesystem::current_path();
};

auto add_build_command(CLI::App &app) -> void;

auto run_build_command(const BuildOptions &options) -> void;

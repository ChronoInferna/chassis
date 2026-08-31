#pragma once

#include <filesystem>

#include <CLI/CLI.hpp>

struct NewOptions {
  std::filesystem::path path = std::filesystem::current_path();
  std::string project_name;
};

auto add_new_command(CLI::App &app) -> void;

auto run_new_command(const NewOptions &options) -> void;

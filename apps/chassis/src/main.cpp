#include <CLI/CLI.hpp>

#include "commands/commands.hpp"
#include "spdlog/spdlog.h"

int main(int argc, char **argv) {
  CLI::App app{"App description"};
  argv = app.ensure_utf8(argv);

  spdlog::set_pattern("[%^%l%$] %v");

  add_init_command(app);
  add_new_command(app);
  add_build_command(app);

  CLI11_PARSE(app, argc, argv);
  return 0;
}

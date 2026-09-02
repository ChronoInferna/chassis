#include <CLI/CLI.hpp>

#include "commands/command.hpp"

#include <gtest/gtest.h>

TEST(CliWiring, RegistersExpectedCommands) {
  CLI::App app{"test"};

  register_all_commands(app);

  EXPECT_NE(app.get_subcommand("init"), nullptr);
  EXPECT_NE(app.get_subcommand("new"), nullptr);
  EXPECT_NE(app.get_subcommand("build"), nullptr);
}

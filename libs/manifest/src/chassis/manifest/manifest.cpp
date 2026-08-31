#include <chassis/manifest/manifest.hpp>

#include <chassis/core/error/error.hpp>
#include <chassis/filesystem/io.hpp>
#include <chassis/filesystem/text_file.hpp>

#include <toml++/toml.hpp>

#include <sstream>

namespace chassis::manifest {

// Helper functions
namespace {

auto toml_to_text_file(const toml::table &table) -> fs::TextFile {
  std::ostringstream oss{};
  oss << table;
  std::string text = oss.str();

  std::vector<std::string> lines{};
  std::istringstream iss{text};
  std::string buffer;

  while (std::getline(iss, buffer)) {
    lines.push_back(std::move(buffer));
  }

  return fs::TextFile{std::move(lines)};
}

auto toml_to_manifest(const toml::table &table) -> Manifest {
  Manifest manifest{};

  if (table.contains("project")) {
    const auto &project_table = table["project"].as_table();
    manifest.package.name =
        project_table->get_as<std::string>("name")->value_or("");
    manifest.package.version =
        project_table->get_as<std::string>("version")->value_or("0.1.0");
  }

  if (table.contains("dependencies")) {
    const auto &dependencies_table = table["dependencies"].as_table();
    for (const auto &[dep_name, dep_value] : *dependencies_table) {
      if (dep_value.is_table()) {
        const auto &dep_table = dep_value.as_table();
        std::string version =
            dep_table->get_as<std::string>("version")->value_or("0.1.0");
        manifest.dependencies.push_back(
            Package{std::string{dep_name.str()}, version});
      }
    }
  }

  return manifest;
}

} // namespace

auto create(std::string_view package_name) -> Manifest {
  return Manifest{
      .package =
          Package{
              .name = std::string{package_name},
              .version = "0.1.0",
          },
  };
}

auto write_manifest(const fs::Path &path, const Manifest &manifest)
    -> Result<void> {
  // TODO validate path as manifest path (i.e. check if it ends with
  // Chassis.toml), if so do it via typing system

  toml::table table{};

  table.emplace("project", toml::table{
                               {"name", manifest.package.name},
                               {"version", manifest.package.version},
                           });

  for (const auto &dep : manifest.dependencies) {
    table["dependencies"].as_table()->insert(
        dep.name, toml::table{{"version", dep.version}});
  }

  fs::TextFile file = toml_to_text_file(table);
  CHASSIS_TRY(fs::write_text_file(path, file, fs::FileWriteMode::Overwrite));

  return {};
}

auto read_manifest(const fs::Path &path) -> Result<Manifest> {
  CHASSIS_TRY_VALUE(text_file, fs::read_text_file(path));

  toml::table table = toml::parse(text_file.text());

  CHASSIS_TRY(manifest::validate(path));

  return toml_to_manifest(table);
}

// TODO
auto validate(const fs::Path &path) -> Result<void> { return {}; }

} // namespace chassis::manifest

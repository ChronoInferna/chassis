#include <chassis/manifest/manifest.hpp>

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
  toml::table table{};

  table.emplace("package", toml::table{
                               {"name", manifest.package.name},
                               {"version", manifest.package.version},
                           });

  fs::TextFile file = toml_to_text_file(table);
  auto res = fs::write_text_file(path / "Chassis.toml", file,
                                 fs::FileWriteMode::Overwrite);

  return res;
}

// auto validate(const fs::Path &path) -> bool {}

} // namespace chassis::manifest

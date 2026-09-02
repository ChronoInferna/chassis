#include <chassis/filesystem/path.hpp>
#include <chassis/manifest/manifest.hpp>

#include <gtest/gtest.h>

namespace chassis::manifest {

TEST(Manifest, CreateDefaultManifest) {
  auto manifest = create("sample-app");

  EXPECT_EQ(manifest.package.name, "sample-app");
  EXPECT_EQ(manifest.package.version, "0.1.0");
  EXPECT_TRUE(manifest.dependencies.empty());
}

TEST(Manifest, ValidateManifestRejectsMissingName) {
  Manifest manifest{};
  manifest.package.version = "0.1.0";

  auto result = validate_manifest(manifest);

  EXPECT_FALSE(result.has_value());
  EXPECT_EQ(result.error().code(), ErrorCode::InvalidManifest);
}

TEST(Manifest, ValidatePathRejectsWrongFileName) {
  auto result = validate("/tmp/not-a-manifest.toml");

  EXPECT_FALSE(result.has_value());
  EXPECT_EQ(result.error().code(), ErrorCode::InvalidManifest);
}

} // namespace chassis::manifest

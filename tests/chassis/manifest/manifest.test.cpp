#include <chassis/manifest/manifest.hpp>

#include <gtest/gtest.h>

namespace chassis::manifest {

TEST(ManifestTest, DefaultConstruction) {
  Manifest m;
  (void)m;
}

} // namespace chassis::manifest

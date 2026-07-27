#include <chassis/filesystem/path.hpp>

#include <filesystem>
#include <gtest/gtest.h>

namespace chassis::fs {

TEST(PathTest, CurrentPath) {
  auto res = chassis::fs::current_path();
  ASSERT_TRUE(res.has_value());
  EXPECT_FALSE(res.value().empty());
  EXPECT_EQ(res.value(), std::filesystem::current_path());
}

TEST(PathTest, Exists) {
  auto cwd = std::filesystem::current_path();
  EXPECT_TRUE(chassis::fs::exists(cwd));
  EXPECT_FALSE(chassis::fs::exists(cwd / "non_existent_file_abcdef_123456"));
}

TEST(PathTest, Canonical) {
  auto cwd = std::filesystem::current_path();
  auto res = chassis::fs::canonical(cwd);
  ASSERT_TRUE(res.has_value());
  EXPECT_EQ(res.value(), std::filesystem::canonical(cwd));

  auto err_res =
      chassis::fs::canonical(cwd / "non_existent_file_abcdef_123456");
  ASSERT_FALSE(err_res.has_value());
  EXPECT_EQ(err_res.error().code(), ErrorCode::FileSystemError);
}

TEST(PathTest, CreateDirectoryAndRemove) {
  auto temp_dir =
      std::filesystem::temp_directory_path() / "chassis_test_dir_1234";
  if (chassis::fs::exists(temp_dir)) {
    auto res = chassis::fs::remove(temp_dir);
    ASSERT_TRUE(res.has_value());
  }

  auto create_res = chassis::fs::create_directory(temp_dir);
  ASSERT_TRUE(create_res.has_value());
  EXPECT_TRUE(chassis::fs::exists(temp_dir));

  auto remove_res = chassis::fs::remove(temp_dir);
  ASSERT_TRUE(remove_res.has_value());
  EXPECT_FALSE(chassis::fs::exists(temp_dir));
}

TEST(PathTest, FindUpward) {
  auto cwd = std::filesystem::current_path();
  auto folder_name = cwd.filename().string();

  auto found = chassis::fs::find_upward(cwd, folder_name);
  ASSERT_TRUE(found.has_value());
  EXPECT_EQ(found.value().filename(), folder_name);

  auto not_found =
      chassis::fs::find_upward(cwd, "non_existent_folder_xyz_9999");
  ASSERT_FALSE(not_found.has_value());
  EXPECT_EQ(not_found.error().code(), ErrorCode::MissingFile);
}

// TODO more find_upward tests

} // namespace chassis::fs

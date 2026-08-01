#include <chassis/core/error/error.hpp>

#include <gtest/gtest.h>

namespace chassis::error {

TEST(Error, CodeAndMessage) {
  EXPECT_EQ(Error(ErrorCode::Success).code(), ErrorCode::Success);
  EXPECT_EQ(Error(ErrorCode::Success).message(), "Success");

  EXPECT_EQ(Error(ErrorCode::InvalidArgument).code(),
            ErrorCode::InvalidArgument);
  EXPECT_EQ(Error(ErrorCode::InvalidArgument).message(), "InvalidArgument");

  EXPECT_EQ(Error(ErrorCode::InvalidConfig).code(), ErrorCode::InvalidConfig);
  EXPECT_EQ(Error(ErrorCode::InvalidConfig).message(), "InvalidConfig");

  EXPECT_EQ(Error(ErrorCode::FileSystemError).code(),
            ErrorCode::FileSystemError);
  EXPECT_EQ(Error(ErrorCode::FileSystemError).message(), "FileSystemError");

  EXPECT_EQ(Error(ErrorCode::MissingFile).code(), ErrorCode::MissingFile);
  EXPECT_EQ(Error(ErrorCode::MissingFile).message(), "MissingFile");

  EXPECT_EQ(Error(ErrorCode::PermissionDenial).code(),
            ErrorCode::PermissionDenial);
  EXPECT_EQ(Error(ErrorCode::PermissionDenial).message(), "PermissionDenial");

  EXPECT_EQ(Error(ErrorCode::ParseError).code(), ErrorCode::ParseError);
  EXPECT_EQ(Error(ErrorCode::ParseError).message(), "ParseError");

  EXPECT_EQ(Error(ErrorCode::ProcessError).code(), ErrorCode::ProcessError);
  EXPECT_EQ(Error(ErrorCode::ProcessError).message(), "ProcessError");

  EXPECT_EQ(Error(ErrorCode::NetworkError).code(), ErrorCode::NetworkError);
  EXPECT_EQ(Error(ErrorCode::NetworkError).message(), "NetworkError");

  EXPECT_EQ(Error(ErrorCode::InternalError).code(), ErrorCode::InternalError);
  EXPECT_EQ(Error(ErrorCode::InternalError).message(), "InternalError");

  EXPECT_EQ(Error(ErrorCode::Other).code(), ErrorCode::Other);
  EXPECT_EQ(Error(ErrorCode::Other).message(), "Other");

  EXPECT_EQ(Error(ErrorCode::Unknown).code(), ErrorCode::Unknown);
  EXPECT_EQ(Error(ErrorCode::Unknown).message(), "Unknown");

  EXPECT_EQ(Error(static_cast<ErrorCode>(999)).message(), "Unknown");
}

TEST(Error, SourceLocation) {
  auto err = Error(ErrorCode::InvalidArgument);
  EXPECT_NE(err.location().file_name(), nullptr);
  EXPECT_GT(err.location().line(), 0u);
}

TEST(Error, AsTextFormat) {
  auto err = Error(ErrorCode::ParseError);
  std::string formatted = err.as_text();
  EXPECT_NE(formatted.find("ParseError"), std::string::npos);
  EXPECT_NE(formatted.find(":"), std::string::npos);
}

TEST(Error, MakeErrorHelper) {
  auto unexp = make_error<int>(ErrorCode::MissingFile);
  EXPECT_EQ(unexp.error().code(), ErrorCode::MissingFile);
  EXPECT_EQ(unexp.error().message(), "MissingFile");

  Result<int> res = make_error<int>(ErrorCode::InvalidArgument);
  ASSERT_FALSE(res.has_value());
  EXPECT_EQ(res.error().code(), ErrorCode::InvalidArgument);
}

} // namespace chassis::error

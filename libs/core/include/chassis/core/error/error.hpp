#pragma once

#include <expected>
#include <source_location>
#include <string_view>

namespace chassis::error {

enum class ErrorCode {
  Success = 0,

  InvalidArgument,
  InvalidConfig,

  MissingFile,
  PermissionDenial,

  ParseError,

  ProcessError,

  NetworkError,

  InternalError,
};

class Error {
public:
  Error(ErrorCode c,
        std::source_location loc = std::source_location::current());

  auto code() const noexcept -> ErrorCode;
  auto message() const noexcept -> std::string_view;

  auto location() const noexcept -> std::source_location;

  auto as_text() const noexcept -> std::string;

private:
  ErrorCode code_;
  std::source_location location_;
};

template <typename T> using Result = std::expected<T, Error>;

} // namespace chassis::error

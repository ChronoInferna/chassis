#pragma once

#include <expected>
#include <source_location>
#include <string_view>

namespace chassis::error {

enum class ErrorCode {
  Success = 0,

  InvalidArgument,
  InvalidConfig,

  FileSystemError,
  MissingFile,
  PermissionDenial,

  ParseError,

  ProcessError,

  NetworkError,

  InternalError,

  Other,
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

template <typename T = void>
auto make_error(ErrorCode c,
                std::source_location loc = std::source_location::current())
    -> std::unexpected<Error> {
  return std::unexpected(Error{c, loc});
}

} // namespace chassis::error

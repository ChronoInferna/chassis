#pragma once

#include <beman/expected/expected.hpp>
// #include <expected>
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

// We use beman::expected for expected over reference support in C++23
namespace expected = beman::expected;
// namespace expected = std;
// TODO this could be an ifdef situation but that's a later problem

template <typename T> using Result = expected::expected<T, Error>;

template <typename E> using Unexpected = expected::unexpected<E>;

template <typename T> using Result = expected::expected<T, Error>;

template <typename T = void>
auto make_error(ErrorCode c,
                std::source_location loc = std::source_location::current())
    -> Unexpected<Error> {
  return Unexpected(Error{c, loc});
}

} // namespace chassis::error

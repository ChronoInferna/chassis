#pragma once

#include <beman/expected/expected.hpp>
#include <source_location>
#include <string_view>

namespace chassis::error {

enum class ErrorCode {
  Success = 0,

  InvalidArgument,
  InvalidManifest,

  FileSystemError,
  MissingFile,
  PermissionDenial,

  ParseError,

  ProcessError,

  NetworkError,

  InternalError,

  Other,
  Unknown,
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
// #include <expected>
// namespace expected = std;
// TODO this could be an ifdef situation but that's a later problem

template <typename T> using Result = expected::expected<T, Error>;

template <typename E> using Unexpected = expected::unexpected<E>;

template <typename T = void>
auto make_error(ErrorCode c,
                std::source_location loc = std::source_location::current())
    -> Unexpected<Error> {
  return Unexpected(Error{c, loc});
}

#define CHASSIS_DETAIL_CONCAT_IMPL(a, b) a##b
#define CHASSIS_DETAIL_CONCAT(a, b) CHASSIS_DETAIL_CONCAT_IMPL(a, b)

#define CHASSIS_TRY_IMPL(name, expr, counter)                                  \
  auto CHASSIS_DETAIL_CONCAT(_chassis_try_result_, counter) = (expr);          \
  do {                                                                         \
    auto _result = (expr);                                                     \
    if (!_result)                                                              \
      return Unexpected(                                                       \
          CHASSIS_DETAIL_CONCAT(_chassis_try_result_, counter).error());       \
  } while (false)

#define CHASSIS_TRY(expr)                                                      \
  CHASSIS_TRY_IMPL(_chassis_try_result_, expr, __COUNTER__)

#define CHASSIS_TRY_VALUE_IMPL(name, expr, counter)                            \
  auto CHASSIS_DETAIL_CONCAT(_chassis_try_result_, counter) = (expr);          \
  if (!CHASSIS_DETAIL_CONCAT(_chassis_try_result_, counter))                   \
    return Unexpected(                                                         \
        CHASSIS_DETAIL_CONCAT(_chassis_try_result_, counter).error());         \
  auto name =                                                                  \
      std::move(CHASSIS_DETAIL_CONCAT(_chassis_try_result_, counter)).value()

#define CHASSIS_TRY_VALUE(name, expr)                                          \
  CHASSIS_TRY_VALUE_IMPL(name, expr, __COUNTER__)

} // namespace chassis::error

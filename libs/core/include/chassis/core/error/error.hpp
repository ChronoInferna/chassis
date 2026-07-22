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

  ErrorCode code() const noexcept;
  std::string_view message() const noexcept;

  std::source_location location() const noexcept;

  std::string as_text() const noexcept;

private:
  ErrorCode code_;
  std::source_location location_;
};

template <typename T> using Result = std::expected<T, Error>;

} // namespace chassis::error

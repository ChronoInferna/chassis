#include <expected>
#include <source_location>
#include <string_view>

namespace chassis::error {

enum class ErrorCode {
  success = 0,

  invalid_argument,
  invalid_config,

  missing_file,
  permission_denial,

  parse_error,

  process_error,

  network_error,

  internal_error,
};

class Error {
public:
  Error(ErrorCode c,
        std::source_location loc = std::source_location::current());

  ErrorCode code() const noexcept;
  std::string_view message() const noexcept;

  std::source_location location() const noexcept;

  std::string_view as_text() const noexcept;

private:
  ErrorCode code_;
  std::source_location location_;
};

template <typename T> using Result = std::expected<T, Error>;

} // namespace chassis::error

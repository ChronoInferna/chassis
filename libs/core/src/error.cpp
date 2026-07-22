#include <chassis/core/error/error.hpp>
#include <format>
#include <source_location>

namespace chassis::error {

Error::Error(ErrorCode c, std::source_location loc)
    : code_(c), location_(loc) {};

ErrorCode Error::code() const noexcept { return code_; }

std::string_view Error::message() const noexcept {
  // TODO eventually use reflection here?
  switch (code_) {
  case ErrorCode::success:
    return "success";
  case ErrorCode::invalid_argument:
    return "invalid_argument";
  case ErrorCode::invalid_config:
    return "invalid_config";
  case ErrorCode::missing_file:
    return "missing_file";
  case ErrorCode::permission_denial:
    return "permission_denial";
  case ErrorCode::parse_error:
    return "parse_error";
  case ErrorCode::process_error:
    return "process_error";
  case ErrorCode::network_error:
    return "network_error";
  case ErrorCode::internal_error:
    return "internal_error";
  default:
    return "unknown error";
  }
}

std::source_location Error::location() const noexcept { return location_; }

std::string Error::as_text() const noexcept {
  return std::format("{}:{}: {}", location_.file_name(), location().line(),
                     message());
}

} // namespace chassis::error

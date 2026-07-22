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
  case ErrorCode::Success:
    return "Success";
  case ErrorCode::InvalidArgument:
    return "InvalidArgument";
  case ErrorCode::InvalidConfig:
    return "InvalidConfig";
  case ErrorCode::MissingFile:
    return "MissingFile";
  case ErrorCode::PermissionDenial:
    return "PermissionDenial";
  case ErrorCode::ParseError:
    return "ParseError";
  case ErrorCode::ProcessError:
    return "ProcessError";
  case ErrorCode::NetworkError:
    return "NetworkError";
  case ErrorCode::InternalError:
    return "InternalError";
  default:
    return "UnknownError";
  }
}

std::source_location Error::location() const noexcept { return location_; }

std::string Error::as_text() const noexcept {
  return std::format("{}:{}: {}", location_.file_name(), location().line(),
                     message());
}

} // namespace chassis::error

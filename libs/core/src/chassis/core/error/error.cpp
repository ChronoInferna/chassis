#include <chassis/core/error/error.hpp>

#include <format>
#include <source_location>

namespace chassis::error {

Error::Error(ErrorCode c, std::source_location loc)
    : code_(c), location_(loc) {};

auto Error::code() const noexcept -> ErrorCode { return code_; }

auto Error::message() const noexcept -> std::string_view {
  // TODO eventually use reflection here?
  switch (code_) {
  case ErrorCode::Success:
    return "Success";
  case ErrorCode::InvalidArgument:
    return "InvalidArgument";
  case ErrorCode::InvalidManifest:
    return "InvalidManifest";
  case ErrorCode::FileSystemError:
    return "FileSystemError";
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
  case ErrorCode::Other:
    return "Other";
  case ErrorCode::Unknown:
    return "Unknown";
  default:
    return "Unknown";
  }
}

auto Error::location() const noexcept -> std::source_location {
  return location_;
}

auto Error::as_text() const noexcept -> std::string {
  return std::format("{}:{}: {}", location_.file_name(), location().line(),
                     message());
}

} // namespace chassis::error

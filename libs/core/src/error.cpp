#include <chassis/core/error/error.hpp>
#include <source_location>

namespace chassis::error {

Error::Error(ErrorCode c, std::source_location loc)
    : code_(c), location_(loc) {};

ErrorCode Error::code() const noexcept { return code_; }

std::string_view Error::message() const noexcept {
  switch (code_) {
    // TODO
  default:
    return "unknown error";
  }
}

std::source_location Error::location() const noexcept { return location_; }

} // namespace chassis::error

#include "infrastructure/logging/logger.hpp"

#include <spdlog/spdlog.h>

namespace chassis::infra::logging {

auto init_logging() -> void { spdlog::set_pattern("[%^%l%$] %v"); }

} // namespace chassis::infra::logging

#pragma once

#include <chassis/process/native_process_runner.hpp>
#include <chassis/process/process_runner.hpp>

namespace chassis::process {

auto run(const Command &command) -> error::Result<Output>;

} // namespace chassis::process

#pragma once

#include <concepts>

namespace chassis::file {

struct File {};

struct TextFile : public File {};

struct BinaryFile : public File {};

template <typename F = File>
concept is_binary_file = std::same_as<F, BinaryFile>;

} // namespace chassis::file

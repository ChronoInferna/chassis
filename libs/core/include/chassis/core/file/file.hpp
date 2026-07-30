#pragma once

namespace chassis::file {

struct File {};

struct TextFile : public File {};

struct BinaryFile : public File {};

} // namespace chassis::file

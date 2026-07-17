#ifndef ERROR_HPP
#define ERROR_HPP

#include <cstdint>

namespace GhostConvert::Error {
enum struct PathError : std::uint8_t { NotFound, NotDirectory };
}
#endif

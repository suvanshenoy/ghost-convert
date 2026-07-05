#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <cstdint>

namespace GhostConvert {
enum class PathError : std::uint8_t { NotFound, NotDirectory };
}
#endif

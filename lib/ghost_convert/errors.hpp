#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <cstdint>

namespace GhostConvert {
enum struct PathError : std::uint8_t { NotFound, NotDirectory };
}
#endif

#include "packages/file_finder/file_finder.hpp"
#include <cstddef>
#include <cstdlib>
#include <span>

using GhostConvert::FileFinder;

auto main(int argc, char **argv) -> int {
  const auto &args = std::span(argv, std::size_t(argc));
  return 0;
}

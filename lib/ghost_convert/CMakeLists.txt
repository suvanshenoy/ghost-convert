cmake_minimum_required(VERSION 3.20..4.3)
add_library(ghost_convert)
file(GLOB_RECURSE SRCS
  "${CMAKE_SOURCE_DIR}/lib/ghost_convert/**/*.cpp"
  "${CMAKE_SOURCE_DIR}/lib/ghost_convert/*.cpp"
)
list(FILTER SRCS EXCLUDE REGEX ".*test\\.cpp$")
target_sources(ghost_convert PUBLIC ${SRCS})

cmake_minimum_required(VERSION 3.20..4.3)
add_library(packages)
file(GLOB_RECURSE SRCS
  "${CMAKE_SOURCE_DIR}/packages/**/*.cpp"
  "${CMAKE_SOURCE_DIR}/packages/*.cpp"
)
target_sources(packages PUBLIC ${SRCS})

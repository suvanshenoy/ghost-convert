cmake_minimum_required(VERSION 3.20..4.2.3)
add_library(tests)
file(GLOB_RECURSE SRCS
  "${CMAKE_SOURCE_DIR}/tests/**/*.cpp"
  "${CMAKE_SOURCE_DIR}/tests/*.cpp"
)
target_sources(tests PUBLIC ${SRCS})

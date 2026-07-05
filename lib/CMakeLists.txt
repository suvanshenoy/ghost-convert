cmake_minimum_required(VERSION 3.20..4.3)
add_library(lib)
file(GLOB_RECURSE SRCS
  "${CMAKE_SOURCE_DIR}/lib/ghost_convert_cli.cpp"
  "${CMAKE_SOURCE_DIR}/lib/ghost_convert_tui.cpp"
)
target_sources(lib PUBLIC ${SRCS})

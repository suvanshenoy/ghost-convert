cmake_minimum_required(VERSION 3.20..4.3)
add_library(apps)
file(GLOB SRCS
  "${CMAKE_SOURCE_DIR}/apps/**/*.cpp"
)
target_sources(apps PUBLIC ${SRCS})

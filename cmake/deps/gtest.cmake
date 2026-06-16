cmake_minimum_required(VERSION 3.20..4.3)
find_package(GTest REQUIRED)
include(FetchContent)
message("Fetching gtest source from git")
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.17.0
)
FetchContent_MakeAvailable(googletest)

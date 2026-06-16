cmake_minimum_required(VERSION 3.20..4.3)
include(FetchContent)
message("Fetching FTXUI source from git")
FetchContent_Declare(
  ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
  GIT_TAG v6.1.9
)
FetchContent_MakeAvailable(ftxui)

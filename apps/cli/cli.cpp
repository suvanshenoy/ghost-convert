#include "cli.hpp"
#include "../../packages/file_finder/file_finder.hpp"
#include <print>
#include <string_view>

using GhostConvert::Cli;
using GhostConvert::FileFinder;

auto Cli::list_files_by_extension(std::string_view arg1, std::string_view arg2) -> void {
  FileFinder file_finder;

  const auto &file_extension =
      arg1.substr(arg1.find("--extension=") + std::string("--extension=").length());

  const auto &search_path =
      arg2.substr(arg2.find("--path=") + std::string("--path=").length());

  const auto &res =
      FileFinder::search_by_extension(file_finder, file_extension, search_path);

  if (!res.has_value()) {
    FileFinder::handle_error(res);
  } else {
    for (const auto &ele : res.value()) {
      std::println("{}", ele);
    }
  }
}

auto Cli::list_files_by_name(std::string_view arg1, std::string_view arg2) -> void {
  FileFinder file_finder;

  const auto &file_name =
      arg1.substr(arg1.find("--name=") + std::string("--name=").length());

  const auto &search_path =
      arg2.substr(arg2.find("--path=") + std::string("--path=").length());

  const auto &res = FileFinder::search_by_name(file_finder, file_name, search_path);

  if (!res.has_value()) {
    FileFinder::handle_error(res);
  } else {
    for (const auto &ele : res.value()) {
      std::println("{}", ele);
    }
  }
}

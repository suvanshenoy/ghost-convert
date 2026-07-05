#include "ghost_convert_cli.hpp"
#include "ghost_convert/file_finder/file_finder.hpp"
#include <print>
#include <sstream>
#include <string_view>

using GhostConvert::Cli;
using GhostConvert::FileFinder;

auto Cli::list_files_by_extension(std::string_view arg1, std::string_view arg2) -> void {
  FileFinder file_finder;

  const auto &file_extension =
      arg1.substr(arg1.find("--extension=") + std::string_view("--extension=").length());

  const auto &search_path =
      arg2.substr(arg2.find("--path=") + std::string_view("--path=").length());

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

auto Cli::list_files_by_name(std::string_view arg1,
                             std::string_view arg2,
                             std::string_view arg3) -> void {
  FileFinder file_finder;

  const auto &file_name =
      arg1.substr(arg1.find("--name=") + std::string_view("--name=").length());

  const auto &search_path =
      arg2.substr(arg2.find("--path=") + std::string_view("--path=").length());

  const auto &case_sensitive = arg3.substr(
      arg3.find("--case-sensitive=") + std::string_view("--case-sensitive=").length());

  bool is_case_sensitive{};
  std::istringstream iss(static_cast<std::string>(case_sensitive));
  iss >> std::boolalpha >> is_case_sensitive;

  const auto &res =
      FileFinder::search_by_name(file_finder, file_name, search_path, is_case_sensitive);

  if (!res.has_value()) {
    FileFinder::handle_error(res);
  } else {
    for (const auto &ele : res.value()) {
      std::println("{}", ele);
    }
  }
}

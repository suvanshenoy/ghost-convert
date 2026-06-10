#include "apps/cli/cli.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <span>
#include <string_view>
#include <vector>

using GhostConvert::Cli;

auto main(int argc, char **argv) -> int {
  const auto &args = std::span(argv, std::size_t(argc));
  std::vector<std::string_view> v_args;

  for (const auto &arg : args) {
    if (static_cast<std::string_view>(arg).contains("--extension") ||
        static_cast<std::string_view>(arg).contains("--path")) {
      v_args.emplace_back(arg);
    }
    if (static_cast<std::string_view>(arg).contains("--name") ||
        static_cast<std::string_view>(arg).contains("--path")) {
      v_args.emplace_back(arg);
    }
  }

  auto check_if_arg_exist = [v_args](std::string_view arg) -> bool {
    return std::ranges::any_of(
        v_args.begin(), v_args.end(), [arg](std::string_view foo) -> bool {
          return foo.substr(0, foo.find('=')) == arg;
        });
  };

  if (check_if_arg_exist("--extension")) {
    Cli::list_files_by_extension(v_args.at(0), v_args.at(1));
  } else if (check_if_arg_exist("--name")) {
    Cli::list_files_by_name(v_args.at(0), v_args.at(1));
  } else {
  }
}

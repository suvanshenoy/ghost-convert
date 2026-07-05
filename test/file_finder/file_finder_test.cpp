#include "../../lib/ghost_convert/errors.hpp"
#include "../../lib/ghost_convert/file_finder/file_finder.hpp"
#include <cstddef>
#include <filesystem>
#include <format>
#include <fstream>
#include <gtest/gtest.h>
#include <string>
#include <vector>

using GhostConvert::FileFinder;
using GhostConvert::PathError;

auto mock_file_finder(std::vector<std::string> mock_files)
    -> std::pair<std::string, std::vector<std::string>> {
  const auto &root_current_path = std::filesystem::current_path();
  std::filesystem::current_path(
      std::format("{}/test/file_finder", root_current_path.string()));

  std::filesystem::create_directory("mock_files");
  const auto &prev_current_path = std::filesystem::current_path().string();

  std::filesystem::current_path(std::format("{}/mock_files", prev_current_path));
  const auto &current_path = std::filesystem::current_path().string();

  for (std::size_t i = 0; i < 2; i++) {
    mock_files.push_back(std::format("{}/{}{}.pdf", current_path, "foo", i + 1));
  }

  std::ofstream outfile;
  for (const auto &mock_file : mock_files) {
    outfile.open(mock_file);
    outfile.close();
  }
  return {current_path, mock_files};
}

TEST(FileFinder, search_by_extension) {
  FileFinder file_finder;
  auto res = mock_file_finder(std::vector<std::string>{});
  const auto &search_by_extension =
      FileFinder::search_by_extension(file_finder, "pdf", res.first);

  if (!search_by_extension.has_value()) {
    FileFinder::handle_error(search_by_extension);
  } else {
    ASSERT_EQ(search_by_extension.value(), std::vector<std::string>{res.second});
  }
}

TEST(FileFinder, search_by_name) {
  FileFinder file_finder;
  auto res = mock_file_finder(std::vector<std::string>{});
  const auto &search_by_name =
      FileFinder::search_by_name(file_finder, "foo1", res.first, true);

  if (!search_by_name.has_value()) {
    FileFinder::handle_error(search_by_name);
  } else {
    res.second.pop_back();
    ASSERT_EQ(search_by_name.value(), std::vector<std::string>{res.second});
  }
}

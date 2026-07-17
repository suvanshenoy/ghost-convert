#include "file_finder.hpp"
#include "../errors.hpp"
#include <algorithm>
#include <cctype>
#include <expected>
#include <filesystem>
#include <print>
#include <ranges>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>
#include <variant>
#include <vector>

using GhostConvert::FileFinder;
using GhostConvert::PathError;

auto FileFinder::search_by_extension(FileFinder &file_finder,
                                     std::string_view file_extension,
                                     std::string_view search_path)
    -> std::expected<std::vector<std::string>,
                     std::variant<std::pair<PathError, std::string>,
                                  std::pair<FileFinderError, std::string>>> {
  std::filesystem::directory_entry path_direntry(search_path);

  if (!path_direntry.exists()) {
    return std::unexpected(
        std::make_pair(PathError::NotFound, path_direntry.path().string()));
  }

  if (!path_direntry.is_directory()) {
    return std::unexpected(
        std::make_pair(PathError::NotDirectory, path_direntry.path().string()));
  }

  for (const auto &path : std::filesystem::recursive_directory_iterator(search_path)) {
    const auto &file_path = path.path().string();
    if (file_path.substr(file_path.find_last_of('.') + 1) == file_extension) {
      file_finder.files.emplace_back(file_path);
    }
  }

  if (file_finder.files.empty()) {
    return std::unexpected(std::make_pair(FileFinder::FileFinderError::FileExtension,
                                          file_extension.data()));
  }

  return file_finder.files;
}

auto FileFinder::search_by_name(FileFinder &file_finder,
                                std::string_view file_name,
                                std::string_view search_path,
                                bool is_case_sensitive = false)
    -> std::expected<std::vector<std::string>,
                     std::variant<std::pair<PathError, std::string>,
                                  std::pair<FileFinderError, std::string>>> {

  std::filesystem::directory_entry path_direntry(search_path);

  if (!path_direntry.exists()) {
    return std::unexpected(
        std::make_pair(PathError::NotFound, path_direntry.path().string()));
  }

  if (!path_direntry.is_directory()) {
    return std::unexpected(
        std::make_pair(PathError::NotDirectory, path_direntry.path().string()));
  }

  for (const auto &path : std::filesystem::recursive_directory_iterator(search_path)) {
    auto file_path = path.path().string();

    std::stringstream ss;
    ss << file_path;
    const auto &untransformed_file_path = ss.str();

    if (is_case_sensitive) {
      std::ranges::transform(file_path.cbegin(),
                             file_path.cend(),
                             file_path.begin(),
                             [](unsigned char arg) -> int { return std::tolower(arg); });
    }

    for (const auto &path : file_path | std::views::split('/')) {
      if (std::ranges::to<std::string>(path).contains(file_name)) {
        file_finder.files.emplace_back(untransformed_file_path);
      }
    }
  }

  if (file_finder.files.empty()) {
    return std::unexpected(
        std::make_pair(FileFinder::FileFinderError::FileName, file_name.data()));
  }

  return file_finder.files;
}

auto FileFinder::handle_error(
    const std::expected<std::vector<std::string>,
                        std::variant<std::pair<PathError, std::string>,
                                     std::pair<FileFinderError, std::string>>> &value)
    -> void {
  if (std::holds_alternative<std::pair<FileFinder::FileFinderError, std::string>>(
          value.error())) {
    const auto &file_finder_error_pair =
        std::get<std::pair<FileFinder::FileFinderError, std::string>>(value.error());

    switch (file_finder_error_pair.first) {
      case FileFinder::FileFinderError::FileExtension:
        std::println("[error] file with extension {} not found",
                     file_finder_error_pair.second);
        break;

      case FileFinder::FileFinderError::FileName:
        std::println("[error] file with name {} not found",
                     file_finder_error_pair.second);
        break;
    }
  } else {
    const auto &path_error_pair =
        std::get<std::pair<PathError, std::string>>(value.error());

    switch (path_error_pair.first) {
      case PathError::NotFound:
        std::println("[error] path {} not found", path_error_pair.second);
        break;

      case PathError::NotDirectory:
        std::println("[error] path {} is not a directory", path_error_pair.second);
        break;
    }
  }
}

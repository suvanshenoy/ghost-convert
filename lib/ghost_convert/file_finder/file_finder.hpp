#ifndef FILE_FINDER_HPP
#define FILE_FINDER_HPP

#include "../error.hpp"
#include <cstdint>
#include <expected>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

using GhostConvert::Error::PathError;

namespace GhostConvert {

struct FileFinder {
  private:
    std::vector<std::string> files;
    enum struct FileFinderError : std::uint8_t { FileExtension, FileName };

  public:
    static auto search_by_extension(FileFinder &file_finder,
                                    std::string_view file_extension,
                                    std::string_view search_path)
        -> std::expected<std::vector<std::string>,
                         std::variant<std::pair<PathError, std::string>,
                                      std::pair<FileFinderError, std::string>>>;

    static auto search_by_name(FileFinder &file_finder,
                               std::string_view file_name,
                               std::string_view search_path,
                               bool is_case_sensitive)
        -> std::expected<std::vector<std::string>,
                         std::variant<std::pair<PathError, std::string>,
                                      std::pair<FileFinderError, std::string>>>;
    static auto handle_error(
        const std::expected<std::vector<std::string>,
                            std::variant<std::pair<PathError, std::string>,
                                         std::pair<FileFinderError, std::string>>> &value)
        -> void;
};
} // namespace GhostConvert

#endif

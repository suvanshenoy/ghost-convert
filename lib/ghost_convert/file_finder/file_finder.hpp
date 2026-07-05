#ifndef FILE_FINDER_HPP
#define FILE_FINDER_HPP

#include "../errors.hpp"
#include <cstdint>
#include <expected>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

namespace GhostConvert {

struct FileFinder {
  private:
    mutable std::vector<std::string> files;
    enum class FileFinderError : std::uint8_t { FileExtension, FileName };

  public:
    static auto search_by_extension(FileFinder &, std::string_view, std::string_view)
        -> std::expected<std::vector<std::string>,
                         std::variant<std::pair<PathError, std::string>,
                                      std::pair<FileFinderError, std::string>>>;

    static auto search_by_name(FileFinder &, std::string_view, std::string_view, bool)
        -> std::expected<std::vector<std::string>,
                         std::variant<std::pair<PathError, std::string>,
                                      std::pair<FileFinderError, std::string>>>;
    static auto handle_error(
        const std::expected<std::vector<std::string>,
                            std::variant<std::pair<PathError, std::string>,
                                         std::pair<FileFinderError, std::string>>> &)
        -> void;
};
} // namespace GhostConvert

#endif

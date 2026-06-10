#ifndef CLI_HPP
#define CLI_HPP
#include <string_view>

namespace GhostConvert {
struct Cli {
    static auto list_files_by_extension(std::string_view, std::string_view) -> void;
    static auto list_files_by_name(std::string_view, std::string_view) -> void;
};
} // namespace GhostConvert

#endif

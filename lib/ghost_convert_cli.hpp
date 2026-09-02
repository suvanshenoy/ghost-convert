#ifndef CLI_HPP
#define CLI_HPP
#include <string_view>

namespace GhostConvert {
struct Cli {
    static auto list_files_by_extension(std::string_view arg1, std::string_view arg2)
        -> void;
    static auto list_files_by_name(std::string_view arg1,
                                   std::string_view arg2,
                                   std::string_view arg3) -> void;
    static auto print_usage() -> void;
};
} // namespace GhostConvert

#endif

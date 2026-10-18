#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include <cctype>
#include <cstdint>
#include <iostream>
#include <regex>
#include <string>
#include <string_view>
#include <vector>

namespace GhostConvert::Parser {

struct JsonParser {
    enum struct Token : std::uint8_t {
      OpenBracket,
      Identifier,
      Colon,
      Integer,
      String,
      Boolean,
      Array,
      Null,
      CloseBracket,
    };

    std::vector<Token> tokens;

  public:
    static auto parse(JsonParser &json_parser, std::string_view json_obj)
        -> decltype(auto) {
      for (const auto &json_obj_token : json_obj) {
        if (json_obj_token == '{') {
          json_parser.tokens.emplace_back(JsonParser::Token::OpenBracket);
        } else if (static_cast<bool>(std::isspace(json_obj_token))) {
          continue;
        } else if (std::regex_search(std::to_string(json_obj_token),
                                     std::regex("([a-z][A-Z]*)"))) {
          json_parser.tokens.emplace_back(JsonParser::Token::Identifier);
        } else if (std::regex_search(std::to_string(json_obj_token),
                                     std::regex("([0-9]*)"))) {
          json_parser.tokens.emplace_back(JsonParser::Token::Integer);
        } else if (json_obj_token == ':') {
          json_parser.tokens.emplace_back(JsonParser::Token::Colon);
        } else if (json_obj_token == '}') {
          json_parser.tokens.emplace_back(JsonParser::Token::CloseBracket);
        } else {
          throw std::runtime_error(
              std::format("token '{}' not implemented", json_obj_token));
        }
      }
      return json_parser.tokens;
    }

    friend auto operator<<(std::ostream &ostream, const std::vector<Token> &tokens)
        -> decltype(auto) {
      ostream << "[";
      for (const auto &token : tokens) {
        switch (token) {
          case JsonParser::Token::OpenBracket:
            ostream << "JsonParser::Token::OpenBracket" << ", ";
            break;
          case JsonParser::Token::Colon:
            ostream << "JsonParser::Token::Colon" << ", ";
            break;
          case JsonParser::Token::Identifier:
            ostream << "JsonParser::Token::Identifier" << ", ";
            break;
          case JsonParser::Token::Integer:
            ostream << "JsonParser::Token::Integer" << ", ";
            break;
          case JsonParser::Token::CloseBracket:
            ostream << "JsonParser::Token::CloseBracket" << ", ";
            break;
          default:
            ostream << " ";
            break;
        }
      }
      ostream << "]";
      return ostream;
    }
};

} // namespace GhostConvert::Parser

#endif

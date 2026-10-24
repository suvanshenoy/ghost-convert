#ifndef JSON_TOKENIZER_HPP
#define JSON_TOKENIZER_HPP

#include <cstdint>
#include <cwctype>
#include <format>
#include <iostream>
#include <stdexcept>
#include <string_view>
#include <vector>

namespace GhostConvert::Tokenizer {

struct JsonTokenizer {
  private:
    enum struct Token : std::uint8_t {
      OpenBracket,
      Identifier,
      Quote,
      Colon,
      Number,
      String,
      Boolean,
      Array,
      Null,
      CloseBracket,
      EndOfFile
    };

    int current_position{};
    char current_character{};
    std::string_view _json_obj;
    std::vector<Token> tokens;

  public:
    explicit JsonTokenizer(std::string_view json_obj) : _json_obj(json_obj) {}

    static auto tokenize(JsonTokenizer &json_tokenizer) -> decltype(auto) {
      for (char json_obj_token : json_tokenizer._json_obj) {
        if (json_obj_token == '{') {
          advance(json_tokenizer);
          json_tokenizer.tokens.push_back(Token::OpenBracket);
        } else if (json_obj_token == '}') {
          json_tokenizer.tokens.push_back(Token::CloseBracket);
        } else if (json_obj_token == '"') {
          advance(json_tokenizer);
          json_tokenizer.tokens.push_back(Token::Quote);
        } else if (static_cast<bool>(std::isspace(json_obj_token))) {
          skip_whitespace(json_tokenizer);
        } else {
          throw std::runtime_error(
              std::format("token '{}' not implemented", json_obj_token));
        }
      }
      return json_tokenizer.tokens;
    }

    static auto skip_whitespace(JsonTokenizer &json_tokenizer) -> void {
      if (static_cast<bool>(std::iswspace(json_tokenizer.current_character))) {
        advance(json_tokenizer);
      }
    }

    static auto advance(JsonTokenizer &json_tokenizer) -> void {
      json_tokenizer.current_position += 1;
      json_tokenizer.current_character =
          json_tokenizer._json_obj.at(json_tokenizer.current_position);
    }

    friend auto operator<<(std::ostream &ostream, const std::vector<Token> &tokens)
        -> decltype(auto) {
      ostream << "[";
      for (const auto &token : tokens) {
        switch (token) {
          case JsonTokenizer::Token::OpenBracket:
            ostream << "JsonTokenizer::Token::OpenBracket" << ", ";
            break;
          case JsonTokenizer::Token::Quote:
            ostream << "JsonTokenizer::Token::Quote" << ", ";
            break;
          case JsonTokenizer::Token::Identifier:
            ostream << "JsonTokenizer::Token::Identifier" << ", ";
            break;
          case JsonTokenizer::Token::Colon:
            ostream << "JsonTokenizer::Token::Colon" << ", ";
            break;
          case JsonTokenizer::Token::Number:
            ostream << "JsonTokenizer::Token::Integer" << ", ";
            break;
          case JsonTokenizer::Token::String:
            ostream << "JsonTokenizer::Token::String" << ", ";
            break;
          case JsonTokenizer::Token::Boolean:
            ostream << "JsonTokenizer::Token::Boolean" << ", ";
            break;
          case JsonTokenizer::Token::Array:
            ostream << "JsonTokenizer::Token::Array" << ", ";
            break;
          case JsonTokenizer::Token::CloseBracket:
            ostream << "JsonTokenizer::Token::CloseBracket" << ", ";
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
} // namespace GhostConvert::Tokenizer

#endif

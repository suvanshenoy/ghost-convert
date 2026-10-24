#include "json_tokenizer.hpp"
#include <gtest/gtest.h>
#include <iostream>

using GhostConvert::Tokenizer::JsonTokenizer;

TEST(JsonTokenizer, tokenize) {
  JsonTokenizer json_tokenizer(R"({"foo": "foo"})");
  std::cout << JsonTokenizer::tokenize(json_tokenizer);
}

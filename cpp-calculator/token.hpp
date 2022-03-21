#pragma once

#include <map>
#include <string>

namespace token
{
  // Precedence of each object
  const std::map<std::string, uint8_t> kPrecedence {
    {"(", 0}, 
    {")", 0}, 
    {"^", 1},
    {"*", 2},
    {"/", 2},
    {"+", 3},
    {"-", 3} 
  };

  // Possible types of token
  enum TokenType {OPERAND, OPERATOR};

  // Represent a single token of the expression
  struct Token {
    std::string symbol;
    uint8_t precedence;
    TokenType tokenType;

    bool operator>(const Token& other);

    // Create a token from a string symbol
    static Token FromString(const std::string& token);
  };

  // bool operator>(Token& self, const Token& other);
}
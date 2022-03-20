#include "token.hpp"

using namespace token;

// Create a token from a string symbol
Token Token::FromString(const std::string& token){
    TokenType tokenType;
    uint8_t precedence;
    // Determine precedence and type
    if (kPrecedence.find(token) != kPrecedence.end())
    {
    tokenType = TokenType::OPERATOR; // Precedence only contains operators so if in the map it must be one.
    precedence = kPrecedence.find(token)->second;
    }
    else{
    tokenType = TokenType::OPERAND;
    precedence = (uint8_t)4;
    }
    
    return Token{token, precedence, tokenType};
};

bool Token::operator>(const Token& other){
  return precedence > other.precedence;
}
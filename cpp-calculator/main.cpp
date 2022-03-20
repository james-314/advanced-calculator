#include <iostream>
#include <iterator>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>

const std::string kLeftBracket = "(";

// Operators that are valid in the expression.
const std::set<std::string> kOperators {"+", "-", "*", "/"};

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

enum TokenType {OPERAND, OPERATOR};

// Represent a single token of the expression
struct Token {
  std::string symbol;
  uint8_t precedence;
  TokenType tokenType;

  bool operator>(const Token& other){
    return precedence > other.precedence;
  }

  // Create a token from a string symbol
  static Token FromString(const std::string& token){
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
  }
};

// Parse the human input to RPN expression.
std::queue<Token> Parse(const std::string& expression)
{
  std::queue<Token> output;
  std::stack<Token> operators;

  // Loop over each character in the expression string.
  for (auto iter = expression.begin(); iter != expression.end(); ++iter)
  {
    Token token = Token::FromString(std::string{ *iter });

    // if number
    if (isdigit(*iter))
    {
      output.push(token);
    }
    // if operator
    else if(kOperators.find(token.symbol) != kOperators.end()){
      while (!operators.empty())
      {
        if (operators.top() > token)
        {
          output.push(operators.top());
          operators.pop();
        }
        else
        {
          break;
        }
      }
      operators.push(token);
    }
    // if left bracket
    else if(token.symbol == "("){
      output.push(token);
    }
    // if right bracket
    else if(token.symbol == ")"){
      while (operators.top().symbol != "(")
      {
        output.push(operators.top());
        operators.pop();
      }
      if (operators.top().symbol == "(")
      {
        operators.pop();
      }
      else{
        std::cout << "Mismatch of brackets" << std::endl;
      }
      
    }
    else{
      // invalid character
      std::cout << "Invalid character in expression: " << token.symbol << std::endl;
    }
  }

  // Pop remaining operators to queue
  while (!operators.empty())
  {
    output.push(operators.top());
    operators.pop();
  }
  

  return output;
}

// Performs the mathematical operation.
float DoOperation(float leftValue, float rightValue, const std::string& operation){
  if (operation == "+")
  {
    return leftValue + rightValue;
  }
  else if (operation == "-")
  {
    return leftValue + rightValue;
  }
  else if (operation == "*")
  {
    return leftValue + rightValue;
  }
  else if (operation == "/")
  {
    return leftValue + rightValue;
  }
  else if (operation == "^")
  {
    return leftValue + rightValue;
  }
  else
  {
    return 0.0;
  }
}

// Evaluate an RPN expression. TODO
float Evaluate(std::queue<Token>& rpnStack) {
  std::stack<Token> evaluationStack;

  while (!rpnStack.empty())
  {
    // If the token is a number then add to stack
    if (rpnStack.front().tokenType == TokenType::OPERAND)
    {
      evaluationStack.push(rpnStack.front());
      rpnStack.pop();
    }
    // If it's an operator then pop numbers from stack and use
    else
    {
      Token firstOperand = evaluationStack.top();
      evaluationStack.pop();
      Token secondOperand = evaluationStack.top();
      evaluationStack.pop();
      float operationResult = DoOperation(std::stof(firstOperand.symbol), std::stof(secondOperand.symbol), rpnStack.front().symbol);
      evaluationStack.push(Token::FromString(std::to_string(operationResult)));
      // Remove the operator token from queue
      rpnStack.pop();
    }
    
  }

  // Return whatever is left on evaluation stack
  return std::stof(evaluationStack.top().symbol);
}

int main()
{
  std::string input;

  while (true)
  {
    std::cout << "Enter an expression to evaluate: ";
    std::getline(std::cin, input);

    if (input.find("exit") != std::string::npos) // Exit key word found
    {
      break;
    } else
    {          
      std::cout << "Your input was interpreted as: " << input << std::endl;
      std::queue<Token> rpnStack = Parse(input);
      float result = Evaluate(rpnStack);
      std::cout << "Answer: " << std::to_string(result) << std::endl;
    }
  }

  std::cout << "Calculator session finished. Press Enter to close the window." << std::endl;
  std::cin.get();
}
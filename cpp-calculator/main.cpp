#include <iostream>
#include <iterator>
#include <map>
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

// Represent a single token of the expression
struct Token {
  // Associativity associativity;
  std::string symbol;
  uint8_t precedence;

  bool operator>(const Token& other){
    return precedence > other.precedence;
  }

  // Create a token from a string symbol
  static Token FromString(const std::string& token){
    uint8_t precedence;
    // Determine precedence
    if (kPrecedence.find(token) != kPrecedence.end())
    {
      precedence = kPrecedence.find(token)->second;
    }
    else{
      precedence = (uint8_t)4;
    }
    
    // return Token{associativity, token, precedence};
    return Token{token, precedence};
  }
};

// Parse the human input to RPN expression.
std::stack<Token> Parse(const std::string& expression)
{
  std::stack<Token> output;
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
double DoOperation(double leftValue, double rightValue, const std::string& operation){
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
double Evaluate(std::stack<Token>& rpnStack) {
  while (!rpnStack.empty())
  {
    std::cout << rpnStack.top().symbol;
    rpnStack.pop();
  }
  return 0.0;
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
      std::stack<Token> rpnStack = Parse(input);
      double result = Evaluate(rpnStack);
    }
  }

  std::cout << "Calculator session finished. Press Enter to close the window." << std::endl;
  std::cin.get();
}
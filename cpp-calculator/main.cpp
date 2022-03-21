#include <cmath>
#include <iostream>
#include <iterator>
#include <map>
#include <queue>
#include <stack>
#include <string>

#include "token.hpp"

// Parse the human input to RPN expression.
std::queue<token::Token> Parse(const std::string& expression)
{
  std::queue<token::Token> output;
  std::stack<token::Token> operators;

  std::string current_number;

  // Loop over each character in the expression string.
  for (auto iter = expression.begin(); iter != expression.end(); ++iter)
  {
    token::Token token = token::Token::FromString(std::string{ *iter });

    // if number
    if (isdigit(*iter) || *iter == '.')
    {
      current_number += *iter;
    }
    else
    {
      // check if there is a number waiting to be added first
      if (!current_number.empty())
      {
        output.push(token::Token::FromString(current_number));
        current_number.clear();
      }
      

      // move on to actually add operator
      // if operator
      if(token::kPrecedence.find(token.symbol) != token::kPrecedence.end()){
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
  }

  // check if there is a number waiting to be added before finishing
  if (!current_number.empty())
  {
    output.push(token::Token::FromString(current_number));
    current_number.clear();
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
    return leftValue - rightValue;
  }
  else if (operation == "*")
  {
    return leftValue * rightValue;
  }
  else if (operation == "/")
  {
    return leftValue / rightValue;
  }
  else if (operation == "^")
  {
    return pow(leftValue, rightValue);
  }
  else
  {
    return 0.0;
  }
}

// Evaluate an RPN expression. TODO
float Evaluate(std::queue<token::Token>& rpnStack) {
  std::stack<token::Token> evaluationStack;

  while (!rpnStack.empty())
  {
    // If the token is a number then add to stack
    if (rpnStack.front().tokenType == token::TokenType::OPERAND)
    {
      evaluationStack.push(rpnStack.front());
      rpnStack.pop();
    }
    // If it's an operator then pop numbers from stack and use
    else
    {
      token::Token firstOperand = evaluationStack.top();
      evaluationStack.pop();
      token::Token secondOperand = evaluationStack.top();
      evaluationStack.pop();
      float operationResult = DoOperation(std::stof(secondOperand.symbol), std::stof(firstOperand.symbol), rpnStack.front().symbol);
      evaluationStack.push(token::Token::FromString(std::to_string(operationResult)));
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
      std::queue<token::Token> rpnStack = Parse(input);
      float result = Evaluate(rpnStack);
      std::cout << "Answer: " << std::to_string(result) << std::endl;
    }
  }

  std::cout << "Calculator session finished. Press Enter to close the window." << std::endl;
  std::cin.get();
}
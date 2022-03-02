#include <iostream>
#include <string>

double evaluate(const std::string& expression) {
    return 0.0;
}

int main()
{
    std::string input;
    std::cout << "Enter an expression to evaluate: ";
    std::getline(std::cin, input);
    std::cout << "Input text: " << input << std::endl;
}
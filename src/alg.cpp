// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

std::string infx2pstfx(std::string inf) {
    std::stringstream postfix;
    std::stack<char> operators;

    for (char c : inf) {
        if (c == ' ') continue;

        if (std::isdigit(c)) {
            postfix << c << ' ';
        } else if (c == '(') {
            operators.push(c);
        } else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix << operators.top() << ' ';
                operators.pop();
            }
            operators.pop();
        } else if (isOperator(c)) {
              while (!operators.empty() && precedence(operators.top()) >= precedence(c)) {
                postfix << operators.top() << ' ';
                operators.pop();
            }
            operators.push(c);
        }
    }

    while (!operators.empty()) {
        postfix << operators.top() << ' ';
        operators.pop();
    }

    return postfix.str();
}

int eval(std::string post) {
    std::stack<int> operands;

    for (char c : post) {
        if (c == ' ') continue;

        if (std::isdigit(c)) {
            operands.push(c - '0');
        } else if (isOperator(c)) {
            int operand2 = operands.top();
            operands.pop();
            int operand1 = operands.top();
            operands.pop();

              switch(c) {
                case '+':
                    operands.push(operand1 + operand2);
                    break;
                case '-':
                    operands.push(operand1 - operand2);
                    break;
                case '*':
                    operands.push(operand1 * operand2);
                    break;
                case '/':
                    operands.push(operand1 / operand2);
                    break;
            }
        }
    }

    return operands.top();
}

int main() {
    std::string infix_expr = "3 + 4 * 2 / (1 - 5)^2";
    std::string postfix_expr = infx2pstfx(infix_expr);    
    std::cout << "Postfix expression: " << postfix_expr << std::endl;
    int result = eval(postfix_expr);
    std::cout << "Result: " << result << std::endl;

    return 0;
}

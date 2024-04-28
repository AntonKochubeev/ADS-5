#include <string>
#include <cctype>
#include <sstream>
#include "include/tstack.h"

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
    TStack<char, 100> operators;

    for (char c : inf) {
        if (c == ' ') continue;

        if (std::isdigit(c)) {
            postfix << c << ' ';
        } else if (c == '(') {
            operators.push(c);
        } else if (c == ')') {
            while (!operators.isEmpty() && operators.peek() != '(') {
                postfix << operators.pop() << ' ';
            }
            operators.pop();
        } else if (isOperator(c)) {
            while (!operators.isEmpty() && precedence(operators.peek()) >= precedence(c)) {
                postfix << operators.pop() << ' ';
            }
            operators.push(c);
        }
    }

    while (!operators.isEmpty()) {
        postfix << operators.pop() << ' ';
    }

    return postfix.str();
}

int eval(std::string post) {
    TStack<int, 100> operands;

    for (char c : post) {
        if (c == ' ') continue;

        if (std::isdigit(c)) {
            operands.push(c - '0');
        } else if (isOperator(c)) {
            int operand2 = operands.pop();
            int operand1 = operands.pop();

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

    return operands.pop();
}

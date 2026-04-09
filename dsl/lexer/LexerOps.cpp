#include <cctype>

#include "Lexer.hpp"

namespace switcher {
    tokenType matchOpPunctType(char symbol){
        switch (symbol) {
            case '-': return tokenType::Minus;
            case '*': return tokenType::Multiply;
            case '/': return tokenType::Divide;
            case '+': return tokenType::Plus;
            case '(': return tokenType::LeftParen;
            case ')': return tokenType::RightParen;
            case '=': return tokenType::Assign;
            case ',': return tokenType::Comma;
            case '%': return tokenType::Percent;
            case '<': return tokenType::LessThan;
            case '>': return tokenType::GreaterThan;
            default:  return tokenType::Unknown;
        }
    }
}
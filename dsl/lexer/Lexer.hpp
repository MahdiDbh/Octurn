#pragma once
#include <vector>

#include "dsl/token/Token.hpp"
#include "log/logHandler.hpp"

struct position{
    std::size_t txtIdx{0};
    std::size_t column{1};
    std::size_t row{1};
};

class Lexer {
private:
    std::vector<Token> tokens_;
    std::string input_;
    position position_;

    char currentSymbol_();
    Token scanToken_();
    void skipSpaces_();
    void newLineCheck_();
public:
    Lexer(std::string_view rawTxt);
    void tokenize();
};


#pragma once
#include <vector>

#include "dsl/token/Token.hpp"
#include "log/logHandler.hpp"
#include "dsl/token/wordTokentypeMap.hpp"

struct position{
    std::size_t txtIdx{0};
    std::size_t column{1};
    std::size_t row{1};
};

enum class status {
    pending,
    over
};

class Lexer {
    private:
        std::string input_;
        position position_;
        status status_;

        char currentSymbol_();

        void scanToken_();
        void skipSpaces_();
        void newLineCheck_();
        void parseWord_(std::string& word);
        void advance_();
        void parseNumber_(std::string& word);
    public:
        Lexer(std::string_view rawTxt);
        void tokenize();
        std::vector<Token> tokens;
};


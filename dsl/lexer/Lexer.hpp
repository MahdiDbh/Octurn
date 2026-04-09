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
        void advance_();
        void emit_(tokenType type, const std::string& lexeme, std::size_t line, std::size_t col);

        void scanToken_();
        void skipSpaces_();
        void newLineCheck_();

        void parseWord_(std::string& word);
        void parseNumber_(std::string& word);
        void parseString_(std::string& word);
        void parseDate_(std::string& word);
        void parseTimeframe_(std::string& word);
        void parsePercent_(std::string& word);

        bool isDate_();
        bool isTimeframe_();
        bool isNumber_();
        bool isPercent_();
    public:
        Lexer(std::string_view rawTxt);
        void tokenize();
        std::vector<Token> tokens;
};

namespace switcher {
    tokenType matchOpPunctType(char symbol);
}

namespace wordMatcher {
    tokenType matchWordType(const std::string& word);
}

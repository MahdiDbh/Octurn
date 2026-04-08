#include "Lexer.hpp"

#include <cctype>

Lexer::Lexer(std::string_view rawTxt) : input_(rawTxt), status_{status::pending}{}

void Lexer::tokenize(){
    tokens.clear();
    position_ = {};
    status_ = status::pending;
    while (status_ == status::pending){
        skipSpaces_();
        newLineCheck_();
        scanToken_();
    }
}

void Lexer::advance_(){
    if (position_.txtIdx < input_.size()){
        position_.txtIdx++;
        position_.column++;
    }
}

char Lexer::currentSymbol_(){
    if (input_.empty() || position_.txtIdx == input_.size()){
        return '\0';
    }
    return input_.at(position_.txtIdx);
}

void Lexer::scanToken_(){
    char c = currentSymbol_();
    if (c == '\0') {
        status_ = status::over;
        tokens.emplace_back(Token{.lexeme = "", .col = position_.column, .line = position_.row, .type = tokenType::EndOfFile});
        return;
    }

    if (std::isalpha((unsigned char)c) || c == '_') {
        const auto startLine = position_.row;
        const auto startCol = position_.column;
        std::string word;
        parseWord_(word);
        tokenType type = wordMatcher::matchWordType(word);
        tokens.emplace_back(Token{.lexeme = word, .col = startCol, .line = startLine, .type = type});
        return;
    }

    if (std::isdigit((unsigned char)c)){
        const auto startLine = position_.row;
        const auto startCol = position_.column;
        std::string number;
        parseNumber_(number);
        tokens.emplace_back(Token{.lexeme = number, .col = startCol,
                                   .line = startLine, .type = tokenType::Number});
        return;
    }

    tokenType op = switcher::matchOpPunctType(c);
    tokens.emplace_back(Token{.lexeme = std::string(1, c), .col = position_.column, .line = position_.row, .type = op});
    advance_();
}

namespace wordMatcher {
    tokenType matchWordType(const std::string& word){
        auto it = wordTokenTypeMap.find(word);
        if (it != wordTokenTypeMap.end()) return it->second;
        return tokenType::Identifier;
    }
}

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

void Lexer::parseWord_(std::string& word){
    char c = currentSymbol_();
    while (std::isalpha((unsigned char)c) || std::isdigit((unsigned char)c) || c == '_'){
        word.push_back(currentSymbol_());
        advance_();
        c = currentSymbol_();
    }
}

void Lexer::parseNumber_(std::string& word){
    char c = currentSymbol_();
    while (std::isdigit((unsigned char)c)) {
        word.push_back(c);
        advance_();
        c = currentSymbol_();
    }

    if (c == '.'){
        const auto nextIdx = position_.txtIdx + 1;
        if (nextIdx < input_.size() && std::isdigit((unsigned char)input_[nextIdx])){
            word.push_back(c);
            advance_();
            c = currentSymbol_();
            while (std::isdigit((unsigned char)c)) {
                word.push_back(c);
                advance_();
                c = currentSymbol_();
            }
        }
    }
}

void Lexer::skipSpaces_(){
    while(currentSymbol_() == ' ' || currentSymbol_() == '\t'){
        advance_();
    }
}

void Lexer::newLineCheck_(){
    while (true){
        char c = currentSymbol_();
        if (c == '\n'){
            advance_();
            position_.row++;
            position_.column = 1;
            continue;
        }
        if (c == '\r'){
            advance_();
            if (currentSymbol_() == '\n'){
                advance_();
            }
            position_.row++;
            position_.column = 1;
            continue;
        }
        break;
    }
}

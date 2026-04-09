#include "Lexer.hpp"

void Lexer::parseWord_(std::string& word){
    char c = currentSymbol_();
    while (std::isalpha((unsigned char)c) || std::isdigit((unsigned char)c) || c == '_'){
        word.push_back(currentSymbol_());
        advance_();
        c = currentSymbol_();
    }
}
#include <cctype>
#include "Lexer.hpp"

namespace wordMatcher {
    tokenType matchWordType(const std::string& word){
        auto it = wordTokenTypeMap.find(word);
        if (it != wordTokenTypeMap.end()) return it->second;
        return tokenType::Identifier;
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
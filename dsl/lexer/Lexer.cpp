#include "Lexer.hpp"

Lexer::Lexer(std::string_view rawTxt) : input_(rawTxt){}

void Lexer::tokenize(){

}

char Lexer::currentSymbol_(){
    if (input_.empty()){
        g_logger.report("Input is empty!");
    }
    return input_.at(position_.txtIdx);
}

Token Lexer::scanToken_(){
    std::string word;
    unsigned char symbol = currentSymbol_();
    while (std::isalnum(symbol) || std::isalpha(symbol)){
        word+= currentSymbol_();
        position_.txtIdx++;
        symbol = currentSymbol_();
    }

    position_.column++;

    tokens_.emplace_back(Token{.col = position_.column, .line = position_.row, .type = })
}

tokenType Lexer::word2Tokentype(){
    
}

void Lexer::skipSpaces_(){
    while(currentSymbol_() == ' '){
        position_.txtIdx++;
    }
}

void Lexer::newLineCheck_(){
    if (currentSymbol_() == '\n'){
        position_.txtIdx++;
        position_.row++;
    }
}
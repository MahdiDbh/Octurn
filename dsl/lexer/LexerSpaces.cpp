#include <cctype>
#include "Lexer.hpp"

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

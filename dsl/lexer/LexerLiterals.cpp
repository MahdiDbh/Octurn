#include <cctype>
#include "Lexer.hpp"

void Lexer::parseDate_(std::string& word){
    for (size_t i = 0; i<10;i++){
        word.push_back(currentSymbol_());
        advance_();
    }
}

void Lexer::parseTimeframe_(std::string& word){
    char c = currentSymbol_();
    while (std::isdigit((unsigned char)c)){
        word.push_back(c);
        advance_();
        c = currentSymbol_();
    }
    char unit = (char)std::tolower((unsigned char)c);
    if (unit == 'm' || unit == 'h' || unit == 'd' || unit == 'w') {
        word.push_back(c);
        advance_();
    }
}

bool Lexer::isTimeframe_(){
    size_t i = position_.txtIdx;
    size_t n = input_.size(); 
    size_t j = i;

    while(j<n && std::isdigit((unsigned char)input_[j])){
        j++;
    }

    if (j == i) return false;
    if (j >= n) return false;

    char unit = (char)std::tolower((unsigned char)input_[j]);
    if (!(unit == 'w' || unit == 'd' || unit == 'h' || unit == 'm')) return false;

    size_t k = j + 1;
    if (k < n && (std::isalnum((unsigned char)input_[k]) || input_[k] == '_')) return false;
    
    return true;
}

bool Lexer::isDateBegin_(){
    size_t i = position_.txtIdx;
    if (i + 9 >= input_.size()) return false;
    for (int k=0; k<4;k++) if (!std::isdigit((unsigned char)input_[i+k])) return false;
    if ((unsigned char)input_[i+4] != '-') return false;
    for (int k=0; k<2;k++) if (!std::isdigit((unsigned char)input_[i+5+k])) return false;
    if ((unsigned char)input_[i+7] != '-') return false;
    for (int k=0; k<2;k++) if (!std::isdigit((unsigned char)input_[i+8+k])) return false;
    return true;
}

void Lexer::parseString_(std::string& word){
    char c = currentSymbol_();
    while (c != '"' && c != '\0'){
        word.push_back(currentSymbol_());
        advance_();
        c = currentSymbol_();
    }
    if (c == '"'){
        advance_();
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

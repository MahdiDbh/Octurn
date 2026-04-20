#include "parser.hpp"
#include "dsl/parser/config/configTokens.hpp"

parser::parser(const std::vector<Token> tokens):tokens_(std::move(tokens)){}

void parser::parse(){
    for (Token token: tokens_){
        if (configTokens.contains(token.type))
    }
}
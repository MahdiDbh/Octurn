#pragma once 

#include <unordered_map>
#include <string>
#include "dsl/token/TokenTypes.hpp"

inline std::unordered_map<std::string, tokenType> wordTokenTypeMap = {
    {"and", tokenType::And},
    {"or", tokenType::Or},

    {"strategy", tokenType::_strategy},
    {"slippage", tokenType::_slippage},
    {"mode", tokenType::_mode},
    {"market", tokenType::_market},
    {"session", tokenType::_session},
    {"capital", tokenType::_capital},
    {"execution", tokenType::_execution},
    {"buy", tokenType::_buy},
    {"risk", tokenType::_risk},
    {"brokerfee", tokenType::_brokerfee},
    {"stoploss", tokenType::_stoploss},
    {"takeprofit", tokenType::_takeprofit},
    {"broker", tokenType::_broker},
    {"range", tokenType::_range},
    {"stop", tokenType::_stop},
    {"take", tokenType::_take},
    
    {"\n", tokenType::NewLine},
    {"\0", tokenType::EndOfFile}
};

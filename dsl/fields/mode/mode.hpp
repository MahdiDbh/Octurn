#pragma once

#include <string>
#include <unordered_map>

enum mode {
    live,
    backtest
};

inline const std::unordered_map<std::string,mode> modeMap = {
    {"live", mode::live},
    {"backtest", mode::backtest}
};
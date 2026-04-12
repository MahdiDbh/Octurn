#pragma once

#include <string>
#include <unordered_map>
#include "dsl/fields/mode/mode.hpp"

inline const std::unordered_map<std::string,mode> modeByName = {
    {"live", mode::live},
    {"backtest", mode::backtest}
};
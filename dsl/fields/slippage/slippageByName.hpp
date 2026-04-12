#pragma once

#include <string>
#include <unordered_map>
#include "dsl/fields/slippage/slippage.hpp"

inline const std::unordered_map<std::string,slippage> slippageByName = {
    {"optimistic", slippage::optimistic},
    {"base", slippage::base},
    {"pessimistic", slippage::pessimistic}
};
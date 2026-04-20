#include <unordered_set>

#include "dsl/token/TokenTypes.hpp"

std::unordered_set<tokenType> configTokens = {
    tokenType::_mode,
    tokenType::_session,
    tokenType::_capital,
    tokenType::_execution,
    tokenType::_slippage,
    tokenType::_broker,
    tokenType::_brokerfee,
    tokenType::_risk,
    tokenType::_dailyMaxLoss,
    tokenType::_maxAccountLoss,
    tokenType::_date,
    tokenType::_range,
};
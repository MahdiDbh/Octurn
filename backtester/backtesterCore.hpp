#pragma once

#include <unordered_map>
#include <algorithm>
#include "interpreter/Interpreter.hpp"
#include "config/config.hpp"
#include "trade/trade.hpp"
#include "account/account.hpp"
#include "execution/ExecutionEngine.hpp"
#include "dataLayer/DataLayer.hpp"

class backtesterCore {
    private:

        std::unordered_map<std::string, AnyValue> data_;
        std::unordered_map<std::string,trade> openTrades_;
        std::unordered_map<std::string,trade> closedTrades_;
        std::vector<std::string> timestampVec_;
        ExecutionEngine executionLayer_;
        DataLayer dataLayer_;

        
        size_t maxSize_;

        void setEntryExit(size_t& i, trade& trade, action actiontype);

        std::string idx2stamp(size_t& idx);

    public:
        config cfg_;
        account account_; 
        backtesterCore(std::unordered_map<std::string, AnyValue>& data, config& cfg, DataLayer& dataLayer_, ExecutionEngine& executionLayer);
        void execute(const std::string& ticker,const std::vector<bool>& entries,const std::vector<bool>& exits);
        void checkEntry(size_t iteration,std::string& ticker);
        void checkEntryExit(size_t iteration, trade& trade_, bool& inTrade, const std::unordered_map<std::string,std::vector<bool>>& entries, const std::vector<bool>& exits);
        void checkExit(size_t iteration);
        bool stopLossHit(trade& trade, double marketPrice);
        void markOpenTradesToMarket(size_t idx);
};

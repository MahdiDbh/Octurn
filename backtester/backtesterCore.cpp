#include "backtesterCore.hpp"
#include "execution/ExecutionEngine.hpp"

#define MIN_BARS_REQ 2

backtesterCore::backtesterCore(std::unordered_map<std::string, AnyValue>& data, config& cfg, DataLayer& viewer,ExecutionEngine& executionLayer) : data_(std::move(data)), cfg_(std::move(cfg)), account_(account(cfg_.equity)), dataLayer_(viewer), executionLayer_(executionLayer) {
    timestampVec_ = *std::get_if<std::vector<std::string>>(&data_["timestamp"]);
    maxSize_ = timestampVec_.size();
    openTrades_.reserve(maxSize_);
};

std::string backtesterCore::idx2stamp(size_t& idx){
    return timestampVec_[idx];
};

void backtesterCore::setEntryExit(size_t& i, trade& trade, action actiontype){
    if (actiontype == action::Entry) {
        trade.timestamp.entryIdx = i+1;
        trade.timestamp.entryTimestamp = idx2stamp(trade.timestamp.entryIdx);
    } else {
        trade.timestamp.exitIdx = i+1;
        trade.timestamp.exitTimestamp = idx2stamp(trade.timestamp.exitIdx);
    }
}

void backtesterCore::checkEntryExit(size_t iteration,trade& trade_, bool& inTrade, const std::vector<bool>& entries, const std::vector<bool>& exits){
    std::string tradeID = trade_.ID;
    if (!inTrade){
        if (entries[iteration] == true && exits[iteration] == false){
            inTrade = true;
            setEntryExit(iteration,trade_,action::Entry);
            openTrades_[tradeID] = trade_;
        }
        else {
            if (exits[iteration] == true){
                setEntryExit(iteration,trade_,action::Exit);
                closedTrades_[tradeID] = trade_;
                openTrades_.erase(tradeID);
                inTrade = false;
                trade_ = trade(trade_.ticker);
            }
        }
    }
}

void backtesterCore::markOpenTradesToMarket(size_t idx){
    double accruedUnrealizedPnl{0};
    for (auto& IdTrade:openTrades_){
        auto& trade = IdTrade.second;
        double marketPrice = dataLayer_.getValue(dataLayer_.makeField(trade.ticker, "open"), idx);
        double delta = account_.markToMarket(marketPrice,trade.price.avgPrice,trade.qty.filledQty,trade.type);
        trade.urealizedPNL = delta;
        accruedUnrealizedPnl+=delta;
    }
    account_.updateUnrealizedPnl(accruedUnrealizedPnl);
    account_.updateEquity();
}

void backtesterCore::checkEntry(size_t iteration,std::string& ticker){
    auto tickerEntries = data_.find(dataLayer_.makeField(ticker,"entries"));
    if (std::get<std::vector<bool>>(tickerEntries->second)[iteration] == true){
        trade openTrade = trade(ticker);
        setEntryExit(iteration,openTrade,action::Entry);
        openTrades_[openTrade.ID] = openTrade;
    }
}

bool backtesterCore::stopLossHit(trade& trade, double marketPrice){
    if (trade.type == ordertype::Buy){
        return (trade.price.stopLossPrice >= marketPrice);
    } else return (trade.price.stopLossPrice <= marketPrice);
}

void backtesterCore::checkExit(size_t iteration){
    for (auto it = openTrades_.begin(); it != openTrades_.end(); ) {
        auto& [id, trade] = *it;

        const auto tickerExits = data_.find(dataLayer_.makeField(trade.ticker,"exits"));
        const double price = dataLayer_.getValue(dataLayer_.makeField(trade.ticker, "open"), iteration);

        if (std::get<std::vector<bool>>(tickerExits->second)[iteration] == true || stopLossHit(trade, price)) {
            trade.status = tradeStatus::CLOSED;
            account_.realizeTradePnL(trade.urealizedPNL);
            setEntryExit(iteration,trade,action::Exit);
            closedTrades_[id] = trade;
            it = openTrades_.erase(it);
        } else {
            ++it;
        }
    }
}

void backtesterCore::execute(const std::string& ticker,const std::vector<bool>& entries,const std::vector<bool>& exits){

    size_t vectSize{entries.size()};

    if (vectSize < MIN_BARS_REQ) {
        throw std::runtime_error("Insufficient data to evaluate strategy");
        return;
    }

    for (size_t i = 0; i < vectSize - 1; i++){
        checkEntryExit(i,trade,inTrade,entries,exits);
        if (!openTrades_.empty()){
            markOpenTradesToMarket(i);
        }
    }
}

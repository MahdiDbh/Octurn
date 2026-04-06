#include "equity.hpp"

Equity::Equity(std::vector<double>&& open,std::vector<double>&& high,std::vector<double>&& low,std::vector<double>&& close,std::vector<double>&& volume, std::vector<uint64_t>&& timestamp){
    symbol_.open = std::move(open);
    symbol_.high = std::move(high);
    symbol_.low = std::move(low);
    symbol_.close = std::move(close);
    symbol_.volume = std::move(volume);
    symbol_.timestamp = std::move(timestamp);
}

void Equity::constructTimestampIdxMap(){
    size_t idx{0};
    timestampIndexMap_.reserve(symbol_.timestamp.size());
    for (const uint64_t& timestamp : symbol_.timestamp){
        timestampIndexMap_[timestamp] = idx;
        idx++;
    }
}
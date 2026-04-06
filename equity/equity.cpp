#include "equity.hpp"

Equity::Equity(std::vector<double>& open,
    std::vector<double>& high,std::vector<double>& low,
    std::vector<double>& close,std::vector<double>& volume, std::vector<uint64_t>& timestamp){
    assetData_["open"] = std::move(open);
    assetData_["high"] = std::move(high);
    assetData_["low"] = std::move(low);
    assetData_["close"] = std::move(close);
    assetData_["volume"] = std::move(volume);
    assetData_["timestamp"] = std::move(timestamp);
}
#include "polygonDataFeed.hpp"
#include <iostream>
#include <cstdint>

polygonDataFeed::polygonDataFeed(polygonClient&& client) : client_(std::move(client)) {};

std::unordered_map<std::string, AnyValue> polygonDataFeed::loadBars(const std::string& ticker,int multiplier,const std::string& from,const std::string& to,const std::string& timespan){
    
    nlohmann::json json = client_.fetchData(ticker,multiplier,from,to,timespan);

    std::vector<double> open, high, low, close, volume;
    std::vector<uint64_t> timestamp;

    auto n = json["results"].size();

    for (auto& marketElement: {&open,&high,&low,&close,&volume}){
        marketElement->reserve(n);
    }

    timestamp.reserve(n);

    for (const auto& bar : json["results"]) {
        open.emplace_back(bar["o"].get<double>());
        high.emplace_back(bar["h"].get<double>());
        low.emplace_back(bar["l"].get<double>());
        close.emplace_back(bar["c"].get<double>());
        volume.emplace_back(bar["v"].get<double>());
        timestamp.emplace_back(bar["t"].get<uint64_t>());
    }
}

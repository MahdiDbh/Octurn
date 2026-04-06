#include "DataInjector.hpp"


DataInjector::DataInjector(std::string& APIKEY, Octurn::EquityMap*& ingestionPtr, std::string& source, connector& connector, nlohmann::json*& JSON) : APIKEY_(std::move(APIKEY)), source_(std::move(source)), 
                            connector_(connector),JSON_(JSON),ingestionPtr_(ingestionPtr){}

void DataInjector::requestEquityData(){
    auto it = apiMapper.find(source_);
    if (it == apiMapper.end()){
        throw std::runtime_error("Octurn doesn't support "+source_+" API. Try another one!");
    }
    std::string URL = it->second(connector_);

    cpr::Response response = cpr::Get(cpr::Url{URL},
                            cpr::Parameters{{"apiKey",APIKEY_}});
    
    JSON_ = &nlohmann::json::parse(response.text);
    
    if (!JSON_->contains("results") || !(*JSON_)["results"].is_array()) {
        throw std::runtime_error("Polygon response has no results[]: " + (*JSON_).dump());
    }
}

void DataInjector::ingestBarsEquity(std::string& ticker){
    requestEquityData();

    std::vector<double> open, high, low, close, volume;
    std::vector<uint64_t> timestamp;

    auto n = (*JSON_)["results"].size();

    for (auto& marketElement: {&open,&high,&low,&close,&volume}){
        marketElement->reserve(n);
    }

    timestamp.reserve(n);

    for (const auto& bar : (*JSON_)["results"]) {
        open.emplace_back(bar["o"].get<double>());
        high.emplace_back(bar["h"].get<double>());
        low.emplace_back(bar["l"].get<double>());
        close.emplace_back(bar["c"].get<double>());
        volume.emplace_back(bar["v"].get<double>());
        timestamp.emplace_back(bar["t"].get<uint64_t>());
    }

    Equity asset = Equity(open,high,low,close,volume,timestamp);
    asset.assetData_["open"] = std::move(open);
    asset.assetData_["high"] = std::move(high);
    asset.assetData_["low"] = std::move(low);
    asset.assetData_["close"] = std::move(close);
    asset.assetData_["volume"] = std::move(volume);
    asset.assetData_["timestamp"] = std::move(timestamp);

    (*ingestionPtr_)[ticker] = asset;
}

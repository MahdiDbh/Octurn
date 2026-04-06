#include "DataInjector.hpp"


DataInjector::DataInjector(std::string& APIKEY, std::string& source, connector& connector, nlohmann::json*& JSON) : APIKEY_(std::move(APIKEY)), source_(std::move(source)), connector_(connector),JSON_(JSON){}

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

std::unordered_map<std::string, Equity> DataInjector::ingestBarsEquity(std::string& ticker){
    requestEquityData();

    std::vector<double> open, high, low, close, volume;
    std::vector<uint64_t> timestamp;

    auto n = (*JSON_)["results"].size();
    std::unordered_map<std::string, Equity> asset;

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
}

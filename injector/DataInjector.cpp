#include "DataInjector.hpp"


DataInjector::DataInjector(std::string& APIKEY, std::string& source, connector& connector) : APIKEY_(std::move(APIKEY)), source_(std::move(source)), connector_(connector){}

nlohmann::json DataInjector::fetchData(){
    auto it = apiMapper.find(source_);
    if (it == apiMapper.end()){
        throw std::runtime_error("Octurn doesn't support "+source_+" API. Try another one!");
    }
    std::string URL = it->second(connector_);

    cpr::Response response = cpr::Get(cpr::Url{URL},
                            cpr::Parameters{{"apiKey",APIKEY_}});
    
    auto json = nlohmann::json::parse(response.text);
    
    if (!json.contains("results") || !json["results"].is_array()) {
        throw std::runtime_error("Polygon response has no results[]: " + json.dump());
    }

    return json;
}

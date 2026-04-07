#include "DataLayer.hpp"
#include <regex>
#include <algorithm>

#include <algorithm>
#include <format>
#include <stdexcept>
#include <utility>

#include "node/Node.hpp"
#include "src/polygon/polygonClient.hpp"

using Octurn::AnyValue;

DataLayer::DataLayer(const std::string& APIKEY, const std::string& source,const connector& connector)
: injector_(APIKEY, &equityMap_, source, connector) {}

void DataLayer::masterTimestamps(){
    std::vector<uint64_t> master;
    for (const auto& [ticker,equity]:equityMap_){

        const auto ts = equity.symbol_.timestamp;
        
        if (ts.empty()) {
            continue;
        }

        for (size_t i = 0; i<ts.size();i++){
            master.emplace_back(ts[i]);
        }
    }

    if (master.empty()){
        throw std::runtime_error("Timestamp vectors are empty");
    }

    std::sort(master.begin(),master.end());
    master.erase(std::unique(master.begin(),master.end()),master.end());
    masterTimestamps_ = std::move(master);

}

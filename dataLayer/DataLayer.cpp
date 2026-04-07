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

void DataLayer::extract(const std::shared_ptr<ASTList>& list) {
    if (!list) {
        return;
    }

    for (auto& data_block : list->list) {
        std::string ticker, timespan, from, to;
        int multiplier = 0;

        if (auto fetching_params_node = std::dynamic_pointer_cast<ASTBlock>(data_block)) {
            auto& fetching_params = fetching_params_node->entries;
            for (auto& [key, value] : fetching_params) {
                if (auto value_node = std::dynamic_pointer_cast<ASTValueNode>(value)) {
                    if (std::holds_alternative<std::string>(value_node->value)) {
                        std::string strVal = std::get<std::string>(value_node->value);
                        if (key == "ticker") ticker = strVal;
                        else if (key == "from") from = strVal;
                        else if (key == "to") to = strVal;
                        else if (key == "timespan") timespan = strVal;
                    } else if (std::holds_alternative<double>(value_node->value)) {
                        if (key == "multiplier") {
                            multiplier = static_cast<int>(std::get<double>(value_node->value));
                        }
                    }
                }
            }
        }

        if (ticker.empty()) {
            throw std::runtime_error("No ticker found");
        }
    }
}

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

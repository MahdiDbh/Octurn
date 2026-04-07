#pragma once
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <nlohmann/json.hpp>

#include "types/types.hpp"
#include "equity/equity.hpp"
#include "src/polygon/polygonDataFeed.hpp"
#include "marketTypes/marketTypes.hpp"
#include "injector/DataInjector.hpp"


struct stampIdx{
    uint64_t earliestStamp;
    uint64_t latestStamp;
};

class DataLayer {
private:
    DataInjector injector_;
    Octurn::EquityMap equityMap_;
    stampIdx timeStampBounds_;
    std::vector<uint64_t> masterTimestamps_;
public:

    DataLayer(const std::string& APIKEY, const std::string& source,const connector& connector);

    void extract(const std::shared_ptr<ASTList>& list);
    void masterTimestamps();
};

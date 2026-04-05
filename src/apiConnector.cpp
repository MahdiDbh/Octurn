#include "apiConnector.hpp"
#include "src/polygon/polygonURL.hpp"


std::unordered_map<std::string,std::function<std::string(connector& connector_)>> apiMapper = {
    {"polygon",[](connector& c){return polygonURL(c.ticker,c.multiplier,c.from,c.timespan,c.to);}}
};
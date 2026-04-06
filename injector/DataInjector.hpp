#include <string>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "src/apiConnector.hpp"
#include "equity/equity.hpp"
#include "types/types.hpp"

class DataInjector {
private:
    std::string APIKEY_;
    std::string source_;
    connector connector_;
    nlohmann::json* JSON_; 
    Octurn::EquityMap* ingestionPtr_;
public:
    DataInjector(std::string& APIKEY, Octurn::EquityMap*& ingestionPtr, std::string& source,connector& connector, nlohmann::json*& JSON);
    void requestEquityData();
    void ingestBarsEquity(std::string& ticker);
};
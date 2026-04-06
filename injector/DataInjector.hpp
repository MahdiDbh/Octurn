#include <string>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "src/apiConnector.hpp"
#include "equity/equity.hpp"

class DataInjector {
private:
    std::string APIKEY_;
    std::string source_;
    connector connector_;
    nlohmann::json* JSON_; 
public:
    DataInjector(std::string& APIKEY,std::string& source,connector& connector,nlohmann::json*& JSON);
    void requestEquityData();
    std::unordered_map<std::string, Equity> ingestBarsEquity(std::string& ticker);
};
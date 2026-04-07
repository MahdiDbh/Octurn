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
    nlohmann::json JSON_; 
    Octurn::EquityMap* ingestionPtr_;
public:
    DataInjector(const std::string& APIKEY, Octurn::EquityMap* ingestionPtr, const std::string& source,const connector& connector);
    void requestEquityData();
    void ingestBarsEquity(const std::string& ticker);
};
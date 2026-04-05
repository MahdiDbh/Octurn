#include <string>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "src/apiConnector.hpp"

class DataInjector {
private:
    std::string APIKEY_;
    std::string source_;
    connector connector_;
public:
    DataInjector(std::string& APIKEY,std::string& source,connector& connector);
    nlohmann::json fetchData();
};
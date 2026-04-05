#include <string>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

class DataInjector {
private:
    std::string api_key;
public:
    DataInjector(std::string& APIKEY);
    nlohmann::json fetchData();
};
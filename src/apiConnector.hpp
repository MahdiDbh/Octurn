#include <unordered_map>
#include <string>
#include <functional>


struct connector {
    std::string& ticker;
    std::string& from;
    std::string& to;
    std::string& timespan;

    int multiplier;
};

extern std::unordered_map<std::string,std::function<std::string(connector& connector)>> apiMapper;

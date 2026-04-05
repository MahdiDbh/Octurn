#include <string>

inline std::string polygonURL(std::string& ticker,int multiplier, std::string& from, std::string& timespan,std::string& to){
    std::string url = "https://api.polygon.io/v2/aggs/ticker/" + ticker +
                      "/range/" + std::to_string(multiplier) + "/" + timespan +
                      "/" + from + "/" + to;
    return url;
}
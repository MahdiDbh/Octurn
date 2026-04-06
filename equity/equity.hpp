#include <vector>
#include <unordered_map>

struct EquityData {
    std::vector<double> open, high, low, close, volume;
    std::vector<uint64_t> timestamp;
};

struct Equity {
    std::unordered_map<uint64_t,size_t> timestampIndexMap_;
    EquityData symbol_;
    

    Equity(std::vector<double>&& open,std::vector<double>&& high,
        std::vector<double>&& low,std::vector<double>&& close,
        std::vector<double>&& volume,std::vector<uint64_t>&& timestamp);

    void constructTimestampIdxMap();
};
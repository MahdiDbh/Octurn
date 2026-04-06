#include <vector>
#include <unordered_map>

struct Equity {
    std::unordered_map<uint64_t,size_t> indexMap_;
    std::unordered_map<std::string,std::variant<std::vector<uint64_t>,std::vector<double>>> assetData_;

    Equity(std::vector<double>& open,std::vector<double>& high,
        std::vector<double>& low,std::vector<double>& close,
        std::vector<double>& volume,std::vector<uint64_t>& timestamp);
};
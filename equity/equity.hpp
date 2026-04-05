#include <vector>
#include <unordered_map>

struct Equity {
    std::string ticker_;
    std::vector<double> open_,high_,low_,close_,volume_;
    std::vector<uint64_t> timestamps_;
    std::unordered_map<uint64_t,size_t> indexMap_;

    Equity(std::string ticker,std::vector<double> open,std::vector<double> high,
    std::vector<double> low,std::vector<double> close,std::vector<double> volume);
};
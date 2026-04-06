#include "equity.hpp"

Equity::Equity(std::vector<double>& open,
                std::vector<double>& high,std::vector<double>& low,
                std::vector<double>& close,std::vector<double>& volume, std::vector<uint64_t>& timestamps) : open_(std::move(open)), high_(std::move(high)),
                low_(std::move(low)), close_(std::move(close)), volume_(std::move(volume)),
                timestamps_(timestamps){}
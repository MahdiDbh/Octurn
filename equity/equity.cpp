#include "equity.hpp"

Equity::Equity(std::string ticker,std::vector<double> open,
std::vector<double> high,std::vector<double> low,
std::vector<double> close,std::vector<double> volume) : open_(std::move(open)),high_(std::move(high)),
low_(std::move(low)),close_(std::move(close)), volume_(std::move(volume)){
    ticker_ = ticker;
}
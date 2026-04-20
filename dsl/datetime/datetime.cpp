#include <ctime>
#include "datetime.hpp"

void datetime::toTimestamp(){
    std::tm t{};
    t.tm_year = std::stoi(year);
    t.tm_mon = std::stoi(month)-1;
    t.tm_mday = std::stoi(day);
    timestamp = static_cast<uint32_t>(std::mktime(&t));
}
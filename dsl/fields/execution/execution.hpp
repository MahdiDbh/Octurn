#pragma once

#include <string>
#include <unordered_map>

enum execution {
    market,
    limit
};

enum fill {
    fok,
    gtc
};

inline const std::unordered_map<std::string,execution> executionMap = {
    {"market", execution::market},
    {"limit", execution::limit}
};

inline const std::unordered_map<std::string,fill> fillMap = {
    {"fok", fill::fok},
    {"gtc", fill::gtc}
};
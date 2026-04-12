#pragma once
#include <string>
#include <unordered_map>

enum session {
    London,
    NewYork,
    Tokyo,
    All
};

inline const std::unordered_map<std::string,session> sessionMap = {
    {"london", session::London},
    {"new-york", session::NewYork},
    {"tokyo", session::Tokyo},
    {"all", session::All}
};
#pragma once
#include <string>
#include "dsl/fields/session/session.hpp"
#include <unordered_map>

inline const std::unordered_map<std::string,session> sessionByName = {
    {"london", session::London},
    {"new-york", session::NewYork},
    {"tokyo", session::Tokyo},
    {"all", session::All}
};
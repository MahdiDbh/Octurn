#pragma once
#include <string>
#include <unordered_map>
#include "dsl/token/TokenTypes.hpp"
#include "namespace/namespace.hpp"

class Validator{
public:
    std::unordered_map<tokenType,Octurn::validationFn> validateByToken;
};



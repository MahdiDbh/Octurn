#pragma once
#include <string>
#include <unordered_map>
#include "dsl/token/TokenTypes.hpp"

class Validator{

private:
    using ValidatorFn = std::unordered_map<tokenType,std::function<bool>>
public:
    Validator(/* args */);
    ~Validator();
};

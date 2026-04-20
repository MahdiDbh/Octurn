#pragma once
#include "dsl/token/TokenTypes.hpp"
#include "namespace/namespace.hpp"

struct validationCtx {
    tokenType token;
    std::string value;
    Octurn::value defvalue;
    Octurn::validationFn fn;
    bool required;
};
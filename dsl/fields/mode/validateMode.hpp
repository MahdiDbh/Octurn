#pragma once

#include <functional>
#include "dsl/validator/ctx/ValidationCtx.hpp"
#include "dsl/token/TokenTypes.hpp"
#include "dsl/token/Token.hpp"
#include "dsl/fields/mode/modeByName.hpp"

validationCtx validateMode = {
    .token = tokenType::_mode,
    .required = true,
    .defvalue = "null",
    .fn = []()->bool{
        return modeByName.find(validateMode.value) != modeByName.end();
    }
};

#pragma once

#include <functional>
#include "dsl/validator/ctx/ValidationCtx.hpp"
#include "dsl/token/TokenTypes.hpp"
#include "dsl/token/Token.hpp"
#include "dsl/fields/execution/executionByName.hpp"
#include "execution.hpp"

validationCtx validateExecution = {
    .token = tokenType::_execution,
    .required = false,
    .defvalue = execution::market,
    .fn = [](){
        return executionByName.find(validateExecution.value) != executionByName.end();
    }
};

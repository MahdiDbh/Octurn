#include "Validator.hpp"
#include "dsl/fields/execution/validateExecution.hpp"
#include "dsl/fields/mode/validateMode.hpp"


std::unordered_map<tokenType,validationCtx> validateByToken = {
    {tokenType::_execution, validateExecution},
    {tokenType::_mode, validateMode}
};
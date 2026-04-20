#include "Validator.hpp"
#include "dsl/fields/execution/validateExecution.hpp"
#include "dsl/fields/mode/validateMode.hpp"
#include "dsl/fields/session/validateSession.hpp"


std::unordered_map<tokenType,validationCtx> validateByToken = {
    {tokenType::_execution, validateExecution},
    {tokenType::_mode, validateMode},
    {tokenType::_session, validateSession}
};
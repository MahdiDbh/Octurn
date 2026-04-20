#pragma once

#include <functional>
#include "dsl/validator/ctx/ValidationCtx.hpp"
#include "dsl/token/TokenTypes.hpp"
#include "dsl/token/Token.hpp"
#include "dsl/fields/session/sessionByName.hpp"
#include "dsl/fields/session/session.hpp"

validationCtx validateMode = {
    .token = tokenType::_session,
    .required = false,
    .defvalue = session::All,
    .fn = []()->bool{
        return sessionByName.find(validateMode.value) != sessionByName.end();
    }
};

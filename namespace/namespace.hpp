#pragma once
#include <variant>
#include <functional>

#include "dsl/fields/execution/execution.hpp"
#include "dsl/fields/session/session.hpp"
#include "dsl/fields/mode/mode.hpp"

namespace Octurn {
    using value = std::variant<std::string,execution,session,mode>;
    using validationFn = std::function<bool,()>
}
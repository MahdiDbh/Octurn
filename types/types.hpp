#pragma once
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>
#include <cstdint>

// ==== Global forward declaration ==== //
struct ASTNode;

namespace Octurn {
    // =================== Namespaces here ================== //
    struct AnyValue;
    using multiValue = std::vector<AnyValue>;
    
    using NodeMap = std::map<std::string, std::shared_ptr<ASTNode>>;
    using taFunctionCall = std::function<std::vector<double>(const multiValue& args,
                                                             std::unordered_map<std::string,AnyValue>& variables_,std::unordered_map<std::string, AnyValue>& data_)>;

    struct AnyValue : std::variant<double, bool, uint64_t, std::string, multiValue, std::vector<double>,std::vector<bool>,std::vector<int>,std::vector<uint64_t>>{
        using base = std::variant<double, bool, uint64_t, std::string, multiValue, std::vector<double>,std::vector<bool>,std::vector<int>,std::vector<uint64_t>>;
        using base::base;
    };

}

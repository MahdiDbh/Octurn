#include <vector>
#include "dsl/token/Token.hpp"
#include "dsl/parser/strategy/strategy.hpp"
class parser {
    private:
        std::unique_ptr<Strategy> root_;
        std::vector<Token> tokens_;
    public:
        parser(const std::vector<Token> tokens);
        void parse();
};

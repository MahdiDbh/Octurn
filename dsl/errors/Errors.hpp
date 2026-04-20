#include <iostream>

struct Errors {
    virtual std::string msg(){
        return "Error";
    }
};

struct SessionError : public Errors {
    std::string msg() override {
        return "Invalid session chosen. 'All' will be used as a default value";
    }
};

struct ModeError : public Errors {
    std::string msg() override {
        return "Invalid mode chosen. 'backtest' will be used as a default value";
    }
};
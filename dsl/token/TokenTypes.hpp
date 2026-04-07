enum class tokenType{
    // SPECIAL
    EndOfFile,
    NewLine,

    // BOOLEAN
    And,
    Or,

    // LITERALS
    String,
    Number,
    Identifier,
    Timeframe,

    // PUNCTUATION
    Assign,
    LeftParen,
    RightParen,
    Comma,
    Percent,


    // COMPARISON OPERATORS
    LessThan,
    GreaterThan,
    LessThanEQ,
    GreaterThanEQ,
    NotEQ,


    // KEYWORDS
    _strategy,
    _slippage,
    _mode,
    _market,
    _session,
    _capital,
    _execution,
    _buy,
    _risk,
    _brokerfee,
    _stoploss,
    _takeprofit,
    _broker
};
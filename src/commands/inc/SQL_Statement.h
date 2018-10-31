#pragma once

namespace cmd{
enum StatementType{
    CREATE_TABLE,
    SHOW_CREATE_TABLE
};

class SQLStatement {
public:
    explicit SQLStatement(StatementType type): type_(type) {};

    StatementType type();
private:
    StatementType type_;
};

} //namespace cmnd

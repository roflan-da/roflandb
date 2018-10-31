#pragma once

namespace cmd{
enum StatementType{
    CREATE_TABLE,
    SHOW_CREATE_TABLE,
    DROP_TABLE
};

class SQLStatement {
public:
    SQLStatement() = default;;
    explicit SQLStatement(StatementType type);

    StatementType type() const;
private:
    StatementType type_;
};

} //namespace cmnd

#include <SQL_Statement.h>

cmd::StatementType cmd::SQLStatement::type() const {
    return type_;
}

cmd::SQLStatement::SQLStatement(cmd::StatementType type): type_(type) {}

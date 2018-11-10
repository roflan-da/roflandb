#include <SQL_Statement.h>

cmd::SQLStatement::SQLStatement(cmd::StatementType type): type_(type) {}

cmd::SQLStatement::SQLStatement() : type_(NONE){}

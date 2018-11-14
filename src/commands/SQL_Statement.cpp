#include <SQL_Statement.h>

cmd::SQLStatement::SQLStatement(cmd::StatementType type): type_(type) {}

cmd::SQLStatement::SQLStatement() : type_(NONE){}

std::string cmd::SQLStatement::get_message() {
    return message_;
}

void cmd::SQLStatement::set_message(std::string message) {
    message_ = message;
}

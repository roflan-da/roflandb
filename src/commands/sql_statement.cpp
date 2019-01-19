#include <sql_statement.h>
#include <insert_statement.h>


cmd::SqlStatement::SqlStatement(cmd::StatementType type) {}

cmd::SqlStatement::SqlStatement() {}

std::string cmd::SqlStatement::get_message() {
    return message_;
}

void cmd::SqlStatement::set_message(std::string message) {
    message_ = message;
}

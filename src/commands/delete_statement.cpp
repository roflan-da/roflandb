#include "delete_statement.h"
#include "storage_engine_exceptions.h"

cmd::DeleteStatement::DeleteStatement(std::string table_name, std::shared_ptr<cond::Condition> conditions) :
    table_name_(table_name), conditions_(conditions){}

bool cmd::DeleteStatement::is_valid() {
    return true;
}

void cmd::DeleteStatement::execute() {

}

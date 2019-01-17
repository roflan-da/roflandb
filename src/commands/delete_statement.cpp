#include "delete_statement.h"
#include "storage_engine_exceptions.h"

cmd::DeleteStatement::DeleteStatement(std::string table_name, std::shared_ptr<cond::Condition> conditions) :
    table_name_(table_name), conditions_(conditions){}

void cmd::DeleteStatement::check_valid() {
    //return true;
}

void cmd::DeleteStatement::execute() {
    st_e::StorageEngine::get_instance().remove(table_name_, conditions_);
}

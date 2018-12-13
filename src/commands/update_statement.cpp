#include "update_statement.h"
#include "storage_engine_exceptions.h"

cmd::UpdateStatement::UpdateStatement(std::string table_name,
                                      std::shared_ptr<std::vector<std::pair<std::string, std::string>>> updated_vals,
                                      std::shared_ptr<cond::Condition> conditions) :
                                      table_name_(table_name),
                                      updated_vals_(updated_vals),
                                      conditions_(conditions){}

void cmd::UpdateStatement::execute() {
    st_e::StorageEngine::get_instance().update(table_name_, updated_vals_, conditions_);
}

bool cmd::UpdateStatement::is_valid() {
    return true;
}

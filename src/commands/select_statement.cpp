#include <select_statement.h>

cmd::SelectStatement::SelectStatement() : SQLStatement(SELECT) {}

cmd::SelectStatement::SelectStatement(std::string table_name, SelectType type) :
        SQLStatement(SELECT),
        table_name_(std::move(table_name)),
        type_(type) {}

void cmd::SelectStatement::execute(st_e::IEngineStorage& storage_engine) {
    //
}

void cmd::SelectStatement::set_col_names(std::shared_ptr<std::vector<std::string>> cols_names) {
    cols_names_ = *cols_names.get();
}

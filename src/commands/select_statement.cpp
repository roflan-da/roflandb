#include <select_statement.h>

cmd::SelectStatement::SelectStatement() : SQLStatement(SELECT) {}

cmd::SelectStatement::SelectStatement(std::string table_name,
        std::shared_ptr<std::vector<std::string>> cols_names,
        SelectType type) :
        SQLStatement(SELECT),
        table_name_(std::move(table_name)),
        cols_names_(*cols_names.get()),
        type_(type) {}

void cmd::SelectStatement::execute(st_e::IEngineStorage& storage_engine) {
    //
}

cmd::SelectStatement::SelectStatement(std::string table_name) : table_name_(table_name), type_(ALL){}

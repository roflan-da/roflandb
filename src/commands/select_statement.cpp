#include <utility>

#include <utility>

#include <utility>
#include <select_statement.h>

cmd::SelectStatement::SelectStatement() = default;

cmd::SelectStatement::SelectStatement(std::string table_name, SelectType type) :
    table_name_(std::move(table_name)),
    type_(type) {}

void cmd::SelectStatement::execute(std::shared_ptr<st_e::IEngineStorage> engine_storage) {
    //
}

void cmd::SelectStatement::set_col_names(std::shared_ptr<std::vector<std::string>> cols_names) {
    cols_names_ = *cols_names.get();
}

#include <utility>

#include <insert_statement.h>


cmd::InsertStatement::InsertStatement() = default;

cmd::InsertStatement::InsertStatement(std::string table_name) : table_name_(std::move(table_name)){

}

std::string cmd::InsertStatement::get_table_name() {
    return table_name_;
}

void cmd::InsertStatement::set_columns_vals(std::shared_ptr<std::vector<std::string>> columns_vals) {
    columns_vals_ = *columns_vals.get();
}

void cmd::InsertStatement::set_columns_names(std::shared_ptr<std::vector<std::string>> columns_names) {
    columns_names_ = *columns_names.get();
}

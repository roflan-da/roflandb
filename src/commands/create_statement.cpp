#include <utility>
#include <create_statement.h>


std::string cmd::CreateStatement::get_table_name() const{
    return table_name_;
}

cmd::CreateStatement::CreateStatement(std::string table_name, std::vector<std::shared_ptr<Column>> n_columns) :
    SQLStatement(CREATE_TABLE),
    table_name_(std::move(table_name)),
    columns_(std::move(n_columns)) {};

cmd::CreateStatement::CreateStatement() :
        SQLStatement(CREATE_TABLE),
        table_name_("") {};

void cmd::CreateStatement::add_column(std::shared_ptr<cmd::Column> column) {
    columns_.emplace_back(column);
}

void cmd::CreateStatement::execute(std::shared_ptr<st_e::IEngineStorage> storage_engine) {
    st_e::TableBuilder table_builder(this->get_table_name());
    auto cols = this->get_columns();
    for (auto col : cols) {
        table_builder.add_column(col->type, col->name);
    }
    auto table = table_builder.build();
    table.Save();
}

std::vector<std::shared_ptr<cmd::Column>> cmd::CreateStatement::get_columns() const {
    return columns_;
}

cmd::CreateStatement::CreateStatement(std::string table_name) :
    SQLStatement(CREATE_TABLE),
    table_name_(std::move(table_name)) {}

void cmd::CreateStatement::set_columns(std::shared_ptr<std::vector<std::shared_ptr<cmd::Column>>> columns) {
    columns_ = *columns.get();
}

cmd::Column::Column(st_e::ColumnType type, std::string name) :
    type(type),
    name(std::move(name)) {}

#include <utility>
#include "create_statement.h"

namespace cmd {

CreateStatement::CreateStatement(std::string table_name,
                                      std::shared_ptr<std::vector<std::shared_ptr<st_e::Column>>> n_columns) :
    SqlStatement(CREATE_TABLE),
    table_name_(std::move(table_name)),
    columns_(*n_columns.get()) {}

CreateStatement::CreateStatement() :
        SqlStatement(CREATE_TABLE),
        table_name_("") {}

void CreateStatement::add_column(std::shared_ptr<st_e::Column> column) {
    columns_.emplace_back(column);
}

void CreateStatement::execute(st_e::IEngineStorage& storage_engine) {
    st_e::TableBuilder table_builder(table_name_);
    table_builder.set_columns(columns_);
    auto table = table_builder.build();
    storage_engine.add_table(table);
    storage_engine.save();
}


} // namespace cmd

#include <utility>
#include "create_statement.h"
#include "storage_engine_exceptions.h"


namespace cmd {

    CreateStatement::CreateStatement() :
            SqlStatement(CREATE_TABLE),
            table_name_("") {}

    CreateStatement::CreateStatement(std::string table_name,
                                     std::shared_ptr<std::vector<std::shared_ptr<st_e::Column>>> n_columns) :
            SqlStatement(CREATE_TABLE),
            table_name_(std::move(table_name)),
            columns_(*n_columns.get()) {}

    void CreateStatement::add_column(std::shared_ptr<st_e::Column> column) {
        columns_.emplace_back(column);
    }

    void CreateStatement::execute() {
        st_e::TableBuilder table_builder(table_name_);
        for (const auto& column : columns_) {
            // todo: consider remove shared_ptr
            table_builder.add_column(*column);
        }
        st_e::StorageEngine::get_instance().add_table(table_builder.build());
    }

    bool CreateStatement::is_valid() const {

        return true;
    }


} // namespace cmd
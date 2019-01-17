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
        check_valid();
//        if (!check_valid()){
//            //TODO: Exception or message
//            throw st_e::StorageEngineException("");
//            return;
//        }
        st_e::TableBuilder table_builder(table_name_);
        for (const auto& column : columns_) {
            // todo: consider remove shared_ptr
            table_builder.add_column(*column);
        }
        st_e::StorageEngine::get_instance().add_table(table_builder.build());
    }

    void CreateStatement::check_valid() {
        for (size_t i = 0; i < columns_.size(); ++i) {
            for (size_t j = i + 1; j < columns_.size(); ++j) {
                if (columns_[i]->name == columns_[j]->name) {
                    throw st_e::CreateDuplicateColumnsException(columns_[i]->name);
                }
            }
        }
        try {
            auto table = st_e::StorageEngine::get_instance().get_table_by_name(table_name_);
        }
        catch (st_e::TableNotExistException& e){
            return;
            //everything is good
        }
        throw st_e::CreateTableAlreadyExistsException(table_name_);
    }


} // namespace cmd
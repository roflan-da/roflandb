#include <utility>

#include <utility>
#include <create_statement.h>

std::string cmd::CreateStatement::get_table_name() const{
    return table_name_;
}

cmd::CreateStatement::CreateStatement(std::string table_name,
                                      std::shared_ptr<std::vector<std::shared_ptr<Column>>> n_columns) :
    SQLStatement(CREATE_TABLE),
    table_name_(std::move(table_name)),
    columns_(std::move(n_columns)) {};

cmd::CreateStatement::CreateStatement() :
        SQLStatement(CREATE_TABLE),
        table_name_(""),
        columns_(nullptr){}

void cmd::CreateStatement::add_column(std::shared_ptr<cmd::Column> column) {
    if (columns_ == nullptr){
        std::vector<std::shared_ptr<Column>> vec;
        columns_ = std::make_shared<std::vector<std::shared_ptr<Column>>>(vec);
    }
    columns_.get()->emplace_back(column);
}

void cmd::CreateStatement::execute(std::shared_ptr<st_e::IEngineStorage> engine_storage) {
    //сохранить таблицу в файл (пишет Серега прямо сейчас)
}

std::shared_ptr<std::vector<std::shared_ptr<cmd::Column>>> cmd::CreateStatement::get_columns() const {
    return columns_;
}

cmd::CreateStatement::CreateStatement(std::string table_name) :
    SQLStatement(CREATE_TABLE),
    table_name_(std::move(table_name)),
    columns_(nullptr){}

cmd::Column::Column(cmd::ColumnType type, std::string name) :
    type(type),
    name(std::move(name)) {}

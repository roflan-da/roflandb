#include <select_statement.h>
#include <iostream>

cmd::SelectStatement::SelectStatement() : SQLStatement(SELECT) {}

cmd::SelectStatement::SelectStatement(std::string table_name,
        std::shared_ptr<std::vector<std::string>> cols_names,
        SelectType type) :
        SQLStatement(SELECT),
        table_name_(std::move(table_name)),
        type_(type),
        cols_names_(*cols_names.get()) {}

void cmd::SelectStatement::execute(st_e::IEngineStorage& storage_engine) {
    st_e::SelectAnswer t = type_ == ALL ? storage_engine.select_all(table_name_) :
           storage_engine.select(table_name_,cols_names_);
    std::string message;
    for (const auto& col_name : t.columns_names){
       message += col_name + " ";
    }
    message += '\n';
    for (const auto row : t.rows){
        for (const auto cell : row){
            message += cell + " ";
        }
        message += '\n';
    }
//    for (int i = 0; t.rows.size() > i; ++i){
//        for (int j = 0; t.rows[i].size() > j; ++j){
//            message += t.rows[i][j] + " ";
//        }
//        message += '\n';
//    }
    set_message(message);
}

cmd::SelectStatement::SelectStatement(std::string table_name) : table_name_(table_name), type_(ALL){}

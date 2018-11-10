#include <select_statement.h>
#include <iostream>

cmd::SelectStatement::SelectStatement() : SQLStatement(SELECT) {}

cmd::SelectStatement::SelectStatement(std::string table_name,
        std::shared_ptr<std::vector<std::string>> cols_names,
        SelectType type) :
        SQLStatement(SELECT),
        table_name_(std::move(table_name)),
        cols_names_(*cols_names.get()),
        type_(type) {}

void cmd::SelectStatement::execute(st_e::IEngineStorage& storage_engine) {
   st_e::SelectAnswer t = storage_engine.select(table_name_,cols_names_);
   for (int i = 0; i < t.columns_names.size(); ++i){
       std::cout << t.columns_names[i] << " ";
   }
   std::cout << std::endl;
    for (int i = 0; i < t.rows.size(); ++i){
        for (int j = 0; j < t.rows[i].size(); ++j){
            std::cout << t.rows[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

cmd::SelectStatement::SelectStatement(std::string table_name) : table_name_(table_name), type_(ALL){}

#include <select_statement.h>
#include <iostream>
#include <sstream>
#include <iomanip>

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
    std::stringstream message_stream;
    std::vector <long long int> maxwidth (t.rows[0].size(),0);
    for (auto &row : t.rows) {
        for (auto cell = 0; cell < row.size(); ++cell) {
            if (row[cell].size() >= maxwidth[cell]){
                maxwidth[cell] = row[cell].size() + 1; //1 for spacing
            }
        }
    }
    for (int i = 0; i < t.columns_names.size(); ++i){
        message_stream << std::setw(maxwidth[i]) << t.columns_names[i];
    }
    message_stream << std::endl;
    for (auto &row : t.rows) {
        for (auto cell = 0; cell < row.size(); ++cell) {
            message_stream << std::setw(maxwidth[cell]) << row[cell];
        }
        message_stream << std::endl;
    }
    message_stream << std::endl;
    message = message_stream.str();
//    for (int i = 0; t.rows.size() > i; ++i){
//        for (int j = 0; t.rows[i].size() > j; ++j){
//            message += t.rows[i][j] + " ";
//        }
//        message += '\n';
//    }
    set_message(message);
}

cmd::SelectStatement::SelectStatement(std::string table_name) : table_name_(table_name), type_(ALL){}

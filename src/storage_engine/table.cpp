#include <utility>

#include "inc/table.h"

namespace st_e {

//Table
Table::Table(TableBuilder builder) {
    name_ = builder.get_table_name();
    columns_types_ = builder.get_columns_types();
    columns_names_ = builder.get_columns_names();

}

std::string Table::get_sql() {
    std::string answer;
    answer = "CREATE TABLE \'" + name_ + "\' (";
    for (int i = 0; i < columns_types_.size(); i++){
        if (i > 0){
            answer += ", ";
        }
        answer += "\'" + columns_names_[i] + "\' " + ENUM_TO_STR(columns_types_[i]);
    }
    answer += ");";
    return answer;
}

std::string Table::Save() {
    std::string table_string;
    table_string = name_ + " " + std::to_string(raws_.size()) + " ";
    for (int i = 0; i < columns_types_.size(); i++){
        table_string += columns_types_[i] + " " + columns_names_[i] + " ";
    }
    return table_string;
}

}//namespace st_e
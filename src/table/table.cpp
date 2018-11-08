#include <utility>

#include "inc/table.h"

namespace st_e {

//Table
Table::Table(TableBuilder builder) {
    name_ = builder.get_table_name();
    columns_ = builder.get_columns();

}

std::string Table::get_sql() {
    std::string answer;
    answer = "CREATE TABLE \'" + name_ + "\' (";
    for (int i = 0; i < (int) columns_.size(); i++){
        if (i > 0){
            answer += ", ";
        }
        answer += "\'" + columns_[i].second + "\' " + ENUM_TO_STR(columns_[i].first);
    }
    answer += ");";
    return answer;
}

std::string Table::Save() {
    std::string table_string;
    table_string = name_ + " " + std::to_string(columns_.size()) + " ";
    for (int i = 0; i < (int) columns_.size(); i++){
        table_string += std::to_string(columns_[i].first) + " " + columns_[i].second + " ";
    }
    return table_string;
}


st_e::Column::Column(st_e::ColumnType type, std::string name) :
        type(type),
        name(std::move(name)) {}


}//namespace st_e
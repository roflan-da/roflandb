#include <utility>

#include "inc/table.h"

namespace st_e {

//IntegerColumn
IntegerColumn::IntegerColumn(std::string name) {
    name_ = std::move(name);
    type_name_ = INT;
}

std::string IntegerColumn::save() {
    std::string column_string;
    column_string = name_ + " " + std::to_string(type_name_) + " ";
    return column_string;
}

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
        answer += "\'" + columns_[i]->get_name() + "\' " + ENUM_TO_STR(columns_[i]->get_type_name());
    }
    answer += ");";
    return answer;
}

std::string Table::Save() {
    std::string table_string;
    table_string = name_ + " " + std::to_string(columns_.size()) + " ";
    for (int i = 0; i < (int) columns_.size(); i++){
        table_string += columns_[i]->save();
    }
    return table_string;
}

//TableBuilder
Table TableBuilder::build() {
    return Table(*this);
}

void TableBuilder::add_column(ColumnType column_type, std::string column_name) {
    if (column_type == INT) {                                           //убрать костыль
        columns_.push_back(std::make_shared<IntegerColumn>(IntegerColumn(std::move(column_name))));
    }
}

}//namespace st_e
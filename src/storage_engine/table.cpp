#include <utility>

#include "inc/table.h"

//IntegerColumn
IntegerColumn::IntegerColumn(std::string name) {
    name_ = std::move(name);
    type_name_ = INT;
}

std::string IntegerColumn::Save() {
    std::string column_string;
    column_string = name_ + " " + std::to_string(type_name_) + " ";
    return column_string;
}

//Table
Table::Table(TableBuilder builder) {
    name_ = builder.getTableName();
    columns_ = builder.getColumns();
}

std::string Table::getSql() {
    std::string answer;
    answer = "CREATE TABLE \'" + name_ + "\' (";
    for (int i = 0; i < columns_.size(); i++){
        if (i > 0){
            answer += ", ";
        }
        answer += "\'" + columns_[i]->getName() + "\' " + std::to_string(columns_[i]->getTypeName());
    }
    answer += ");";
    return answer;
}

std::string Table::Save() {
    std::string table_string;
    table_string = name_ + " " + std::to_string(columns_.size()) + " ";
    for (int i = 0; i < columns_.size(); i++){
        table_string += columns_[i]->Save();
    }
    return table_string;
}

//TableBuilder
Table TableBuilder::build() {
    return Table(*this);
}

void TableBuilder::addColumn(ColumnType column_type, std::string column_name) {
    if (column_type == INT) {                                           //убрать костыль
        columns_.push_back(std::make_shared<IntegerColumn>(IntegerColumn(std::move(column_name))));
    }
}
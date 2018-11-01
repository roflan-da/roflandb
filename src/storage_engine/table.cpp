#include <utility>

#include "inc/table.h"

//IntegerColumn
IntegerColumn::IntegerColumn(std::string name) {
    name_ = std::move(name);
    type_name_ = "INT";
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
        answer += "\'" + columns_[i]->getName() + "\' " + columns_[i]->getTypeName();
    }
    answer += ");";
    return answer;
}

//TableBuilder
Table TableBuilder::build() {
    return Table(*this);
}

void TableBuilder::addColumn(std::string column_type, std::string column_name) {
    if (column_type == "INT") {                                           //убрать костыль
        columns_.push_back(std::make_shared<IntegerColumn>(IntegerColumn(std::move(column_name))));
    }
}
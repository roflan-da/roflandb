#include <exception>
#include <table.h>

#include "table.h"
#include "storage_engine_exceptions.h"

namespace st_e {

std::string Column::get_type_string() const {
    switch (type){
        case INT:
            return "INT";
        case STRING:
            return "STRING";
        case CHAR:
            return "CHAR";
        case TEXT:
            return "TEXT";
        default:
            throw std::range_error("Column type to string conversion doesn't exist");
    }
}

Column::Type Column::get_type_from_string(std::string& type) {
    if (type == "INT") {
        return Type::INT;
    } else if (type == "STRING") {
        return Type::STRING;
    } else if (type == "CHAR") {
        return Type::CHAR;
    } else if (type == "TEXT") {
        return Type::TEXT;
    }

    throw std::range_error("Column string to type conversion doesn't exist");
}

std::string Table::get_sql() const {
    std::string sql = "CREATE TABLE \'" + name_ + "\' (";

    for (size_t i = 0; i < columns_.size(); i++){
        if (0 < i && i < columns_.size() - 1) {
            sql += ", ";
        }
        sql += "`" + columns_[i].name + "` " + columns_[i].get_type_string();
    }
    sql += ");";
    return sql;
}

TableBuilder& TableBuilder::add_column(Column::Type type, const std::string& name) {
    columns_.emplace_back(type, name);
    return *this;
}

TableBuilder& TableBuilder::add_column(Column& column) {
    columns_.emplace_back(column);
    return *this;
}
} // namespace st_e

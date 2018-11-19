#include <exception>
#include <table.h>
#include <boost/algorithm/string.hpp>

#include "table.h"
#include "storage_engine_exceptions.h"
#include "configuration.h"


namespace fs = boost::filesystem;

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

    fs::path Table::get_metadata_file_path(const std::string& table_name) {
        auto invariant_table_name = boost::to_lower_copy(table_name);

        // **/{data_dir_path}/{table_name}/{table_name.meta}
        auto meta_data_file_path = fs::current_path() /= fs::path(DATA_DIR_PATH) /= fs::path(invariant_table_name)
                /= fs::path(table_name + ".meta");

        return meta_data_file_path.string();
    }

    boost::filesystem::path Table::get_data_file_path(const std::string& table_name) {
        auto invariant_table_name = boost::to_lower_copy(table_name);

        // **/{data_dir_path}/{table_name}/{table_name.data}
        auto meta_data_file_path = fs::current_path() /= fs::path(DATA_DIR_PATH) /= fs::path(invariant_table_name)
                /= fs::path(table_name + ".data");

        return meta_data_file_path.string();
    }

} // namespace st_e

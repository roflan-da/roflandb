#include <exception>
#include <boost/algorithm/string.hpp>
#include <table.h>


#include "table.h"
#include "storage_engine_exceptions.h"
#include "configuration.h"


namespace fs = boost::filesystem;

namespace st_e {

std::string Column::get_type_string() const {
    switch (type){
        case INT:
            return "INT";
        case VARCHAR:
            return "VARCHAR";
        case CHAR:
            return "CHAR";
        case TEXT:
            return "TEXT";
        case BOOL:
            return "BOOL";
        default:
            throw std::range_error("Column type to string conversion doesn't exist");
    }
}

Column::Type Column::get_type_from_string(std::string& type) {
    if (type == "INT") {
        return Type::INT;
    } else if (type == "VARCHAR") {
        return Type::VARCHAR;
    } else if (type == "CHAR") {
        return Type::CHAR;
    } else if (type == "TEXT") {
        return Type::TEXT;
    } else if (type == "BOOL") {
        return Type::BOOL;
    }

    throw std::range_error("Column string to type conversion doesn't exist");
}

uint32_t Column::deserialize(const std::vector<char>& input, TableRow::ArrayOfCells& cells, size_t offset) const {
    auto start_ptr = input.data() + offset;

    if (type == INT) {
        uint32_t val = 0;
        std::memcpy(&val, start_ptr, sizeof(uint32_t));
        cells.emplace_back(new IntegerTableCell(val));
        return sizeof(uint32_t);
    }

    if (type == BOOL) {
        bool val = false;
        std::memcpy(&val, start_ptr, sizeof(bool));
        cells.emplace_back(new BoolTableCell(val));
        return sizeof(bool);
    }

    throw CrutchException();
}

std::string Table::get_sql() const {
    std::string sql = "CREATE TABLE \'" + name_ + "\' (";

    size_t i = 0;
    for (const auto& column : ordered_columns_) {
        if (0 < i && i < columns_orders_.size() - 1) {
            sql += ", ";
        }

        sql += "`" + column.name + "` " + column.get_type_string();
        i++;
    }

    sql += ");";
    return sql;
}

TableBuilder& TableBuilder::add_column(Column::Type type, const std::string& name) {
    auto order = (unsigned int)ordered_columns_.size();
    columns_orders_.emplace(name, order);
    ordered_columns_.emplace_back(Column(type, name));
    return *this;
}

TableBuilder& TableBuilder::add_column(Column& column) {
    auto order = (unsigned int)ordered_columns_.size();
    columns_orders_.emplace(column.name, order);
    ordered_columns_.emplace_back(column);
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

boost::filesystem::path Table::get_metadata_file_path() const {
    return get_metadata_file_path(name_);
}

boost::filesystem::path Table::get_data_file_path() const {
    return get_data_file_path(name_);
}

} // namespace st_e

#pragma once

#include <memory>
#include <string>
#include <vector>
#include <map>
#include <boost/filesystem.hpp>
#include "table_cells.h"

namespace st_e {

class Column {
public:
    enum Type {INT, CHAR, VARCHAR, TEXT, BOOL};

    Type type;
    std::string name;
    std::string get_type_string() const;
    // Todo: remove copy paste
    static Type get_type_from_string(std::string& type);

    Column(Type type, const std::string& name) : type(type), name(name) {}
    // returns number of used bytes
    virtual uint32_t deserialize(std::ifstream& input, TableRow::ArrayOfCells& cells) const;
};

class VarcharColumn : public Column {
public:
    VarcharColumn(Type type, const std::string& name, int length) : Column(type, name), length(length) {}
    int length;
};

class Table {
public:
    using OrderType = unsigned long long;
    using ArrayOfColumns = std::vector<Column>;
    using MapOfColumns = std::map<std::string, OrderType>;

    explicit Table(const std::string& name, const MapOfColumns& columns_order, const ArrayOfColumns& ordered_columns)
        : name_(name), columns_orders_(columns_order), ordered_columns_(ordered_columns) {}

    std::string get_sql() const;
    std::string get_name() const { return name_; }
    MapOfColumns& get_columns_orders() { return columns_orders_; }
    const ArrayOfColumns& get_ordered_columns() const { return ordered_columns_; }

    const Column& get_column(const std::string& name) { return ordered_columns_[columns_orders_[name]]; }

    static boost::filesystem::path get_metadata_file_path(const std::string& table_name);
    static boost::filesystem::path get_data_file_path(const std::string& table_name);

    boost::filesystem::path get_metadata_file_path() const;
    boost::filesystem::path get_data_file_path() const;

private:
    std::string name_;
    MapOfColumns columns_orders_;
    ArrayOfColumns ordered_columns_;
};

class TableBuilder {
public:
    explicit TableBuilder(const std::string& table_name) : table_name_(table_name) {}

    TableBuilder& add_column(Column::Type type, const std::string& name);
    TableBuilder& add_column(Column& column);

    Table build() {
        return Table(table_name_, columns_orders_, ordered_columns_);
    }

private:
    std::string table_name_;
    Table::MapOfColumns columns_orders_;
    std::vector<Column> ordered_columns_;
};

}//namespace st_e

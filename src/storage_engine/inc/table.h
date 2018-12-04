#pragma once

#include <memory>
#include <string>
#include <vector>
#include <map>
#include <boost/filesystem.hpp>

namespace st_e {

class Column {
public:
    enum Type {INT, CHAR, VARCHAR, TEXT, BOOL};

    Column(Type type, const std::string& name) : type(type), name(name) {}

    Type type;
    std::string name;
    std::string get_type_string() const;
    // Todo: remove copypaste
    static Type get_type_from_string(std::string& type);
};

class VarcharColumn : public Column {
public:
    VarcharColumn(Type type, const std::string& name, int length) : Column(type, name), length(length) {}
    int length;
};

class Table {
public:
    using ArrayOfColumns = std::vector<Column>;
    using MapOfColumns = std::map<std::string, Column>;

    explicit Table(const std::string& name, const MapOfColumns& columns, const ArrayOfColumns& ordered_columns)
        : name_(name), columns_(columns), ordered_columns_(ordered_columns) {}

    std::string get_sql() const;
    std::string get_name() const { return name_; }
    const MapOfColumns& get_columns() const { return columns_; }
    const ArrayOfColumns& get_ordered_columns() const { return ordered_columns_; }

    static boost::filesystem::path get_metadata_file_path(const std::string& table_name);
    static boost::filesystem::path get_data_file_path(const std::string& table_name);

    boost::filesystem::path get_metadata_file_path() const;
    boost::filesystem::path get_data_file_path() const;

private:
    std::string name_;
    MapOfColumns columns_;
    ArrayOfColumns ordered_columns_;
};

class TableBuilder {
public:
    explicit TableBuilder(const std::string& table_name) : table_name_(table_name) {}

    TableBuilder& add_column(Column::Type type, const std::string& name);
    TableBuilder& add_column(Column& column);

    Table build() {
        return Table(table_name_, columns_, ordered_columns_);
    }

    const std::map<std::string, Column>& get_columns() const { return columns_; };

private:
    std::string table_name_;
    std::map<std::string, Column> columns_;
    std::vector<Column> ordered_columns_;
};

}//namespace st_e

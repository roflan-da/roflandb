#pragma once

#include <memory>
#include <string>
#include <vector>

namespace st_e {

class Column {
public:
    enum Type {INT, STRING, CHAR, TEXT};

    Column(Type type, const std::string& name) : type(type), name(name) {}

    Type type;
    std::string name;
    std::string get_type_string() const;
    // Todo: remove copypaste
    static Type get_type_from_string(std::string& type);
};

class Table {
public:
    explicit Table(const std::string& name, const std::vector<Column>& columns)
        : name_(name), columns_(columns) {}

    std::string get_sql() const;
    std::string get_name() const { return name_; }
    const std::vector<Column>& get_columns() const { return columns_; }

private:
    std::string name_;
    std::vector<Column> columns_;
};

class TableBuilder {
public:
    explicit TableBuilder(const std::string& table_name) : table_name_(table_name) {}

    TableBuilder& add_column(Column::Type type, const std::string& name);
    Table build() {
        return Table(table_name_, columns_);
    }

    const std::vector<Column>& get_columns() const { return columns_; };

private:
    std::string table_name_;
    std::vector<Column> columns_;
};

}//namespace st_e

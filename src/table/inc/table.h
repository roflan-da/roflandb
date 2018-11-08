#pragma once

#include <utility>

#include <memory>
#include <string>
#include <vector>    //юзать вектор или нет?

namespace st_e {

#define ENUM_TO_STR(ENUM) std::string(#ENUM)

class Table;

//class Column;

//class IntegerColumn;

class TableBuilder;

enum ColumnType{
    INT,
    STRING,
    CHAR,
    TEXT
};

class TableCell{
public:
    virtual std::string get_data() = 0;
};

class IntegerTableCell : public TableCell{
public:
    explicit IntegerTableCell(int data){
        data_ = data;
    }

    std::string get_data() override{
        return std::to_string(data_);
    }

private:
    int data_;
};

class TableRaw{
public:
    //добавление мб в конструкторе, мб методом, мб надо еще и удалять

private:
    std::vector<std::shared_ptr<TableCell>> cells_;
};

class Table {
public:
    friend TableBuilder;
    std::string get_sql();
    std::string get_name(){
        return name_;
    }
    std::string Save();
    //void Load(std::ostream in);
private:
    explicit Table(TableBuilder builder);
    std::string name_;
    std::vector<ColumnType> columns_types_;
    std::vector<std::string> columns_names_;
    std::vector<std::shared_ptr<TableRaw>> raws_;
};

class TableBuilder {
public:
    friend Table;
    explicit TableBuilder(std::string table_name) :
            table_name_(std::move(table_name)) {}

    void set_columns_types(std::vector<ColumnType> column_types){
        column_types_ = std::move(column_types);
    }

    void set_columns_names(std::vector<std::string> column_names){
        column_names_ = std::move(column_names);
    }

    Table build() {
        return Table(*this);
    }

private:
    std::vector<ColumnType> get_columns_types(){
        return std::move(column_types_);
    }

    std::vector<std::string> get_columns_names(){
        return std::move(column_names_);
    }
  
    std::string get_table_name(){
        return table_name_;
    }

    std::string table_name_;
    std::vector<ColumnType> column_types_;
    std::vector<std::string> column_names_;

};

}//namespace st_e
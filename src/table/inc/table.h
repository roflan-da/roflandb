#pragma once

#include <utility>

#include <memory>
#include <string>
#include <vector>    //юзать вектор или нет?

namespace st_e {

class Table;

class TableBuilder;

enum ColumnType{
    INT,
    STRING,
    CHAR,
    TEXT
};

static std::string EnumToString(ColumnType columnType){   //мб заменить на map | static?
    switch (columnType){
        case INT:
            return "INT";
        default:
            return "";
    }
}

struct Column{
    Column(st_e::ColumnType type, std::string name);

    st_e::ColumnType type;
    std::string name;
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
    //todo: fix;
    explicit Table(TableBuilder builder);
private:

    std::string name_;
    std::vector<std::shared_ptr<Column>> columns_;
    std::vector<std::shared_ptr<TableRaw>> raws_;
};

class TableBuilder {
public:
    friend Table;
    explicit TableBuilder(std::string table_name) :
            table_name_(std::move(table_name)) {}

    void set_columns(std::vector<std::shared_ptr<Column>> columns){
        columns_ = std::move(columns);
    }

    std::shared_ptr<Table> build() {
        return std::make_shared<Table>(*this);
    }

private:
    std::vector<std::shared_ptr<Column>> get_columns(){
        return std::move(columns_);
    }
  
    std::string get_table_name(){
        return table_name_;
    }

    std::string table_name_;
    std::vector<std::shared_ptr<Column>> columns_;

};

}//namespace st_e
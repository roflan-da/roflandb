#pragma once

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
    TEXT,
    NONE
};

struct Column {
    Column(ColumnType type, std::string name);

    ColumnType type;
    std::string name;
};

struct SelectAnswer {
    std::vector<std::string> columns_names;
    std::vector<std::vector<std::string>> rows;
};

class TableCell {
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

class TableRow{
public:
    explicit TableRow(std::vector<std::shared_ptr<TableCell>> cells){
        cells_ = std::move(cells);
    }

    std::string get_cell(size_t number){
        return cells_[number]->get_data();
    }

    std::string to_string();

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
    std::string to_string();
    std::string enum_to_string(ColumnType columnType);//мб заменить на map
    std::shared_ptr<TableCell> create_cell(std::pair<std::string, std::string> cell);
    std::shared_ptr<TableCell> create_cell(std::pair<ColumnType, std::string> cell);
    void insert(std::vector<std::pair<std::string, std::string>> row);
    void insert(std::vector<std::pair<ColumnType, std::string>> row);
    SelectAnswer select(std::vector<std::string> columns_names);
    SelectAnswer select_all();
    ColumnType get_column_type(std::string column_name);
    //todo: fix;
    explicit Table(TableBuilder builder);
private:

    std::string name_;
    std::vector<std::shared_ptr<Column>> columns_;  //заменить на map
    std::vector<std::shared_ptr<TableRow>> rows_;
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
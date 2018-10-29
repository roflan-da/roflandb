#pragma once

#include <memory>
#include <string>
#include <vector>    //юзать вектор или нет?

class Table;

class Column;

class IntegerColumn;

class TableBuilder;

class Column {
public:
    std::string getName(){
        return name_;
    }

    std::string getTypeName(){
        return type_name;
    }

protected:
    std::string name_;
    std::string type_name;
};

class IntegerColumn : public Column {
public:
    IntegerColumn(std::string name);

private:
    std::vector<int> data_;       //мб можно темплейт как то прикрутить
};

class Table {
public:
    Table(TableBuilder builder);
    std::string getSql();
private:
    std::string name_;
    std::vector<std::shared_ptr<Column>> columns_;
};

class TableBuilder {
public:
    TableBuilder(std::string table_name) {
        table_name_ = table_name;
    }

    void addColumn(std::string column_type, std::string column_name);

    Table build();

    std::string getTableName(){
        return table_name_;
    }

    std::vector<std::shared_ptr<Column>> getColumns(){
        return std::move(columns_);             //я умный или наоборот?
    }

private:
    std::string table_name_;
    std::vector<std::shared_ptr<Column>> columns_;
};

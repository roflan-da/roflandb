#pragma once

#include <utility>

#include <memory>
#include <string>
#include <vector>    //юзать вектор или нет?

namespace st_e {

#define ENUM_TO_STR(ENUM) std::string(#ENUM)

class Table;

class Column;

class IntegerColumn;

class TableBuilder;

enum ColumnType{
    INT,
    STRING,
    CHAR,
    TEXT
};

class Column {
public:
    std::string get_name(){
        return name_;
    }

    ColumnType get_type_name(){
        return type_name_;
    }

    virtual std::string save() = 0;
    //virtual void Load(std::ostream in) = 0;

protected:
    std::string name_;
    ColumnType type_name_;
};

class IntegerColumn : public Column {
public:
    explicit IntegerColumn(std::string name);
    std::string save() override;
    // Load(std::ostream in) override;

private:
    std::vector<int> data_;       //мб можно темплейт как то прикрутить
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
    std::vector<std::shared_ptr<Column>> columns_;
};

class TableBuilder {
public:
    friend Table;
    explicit TableBuilder(std::string table_name) :
            table_name_(std::move(table_name)) {}

    void add_column(ColumnType column_type, std::string column_name);

    Table build();

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
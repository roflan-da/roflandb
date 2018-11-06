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
    std::string getName(){
        return name_;
    }

    ColumnType getTypeName(){
        return type_name_;
    }

    virtual std::string Save() = 0;
    //virtual void Load(std::ostream in) = 0;

protected:
    std::string name_;
    ColumnType type_name_;
};

class IntegerColumn : public Column {
public:
    explicit IntegerColumn(std::string name);
    std::string Save() override;
    // Load(std::ostream in) override;

private:
    std::vector<int> data_;       //мб можно темплейт как то прикрутить
};

class Table {
public:
    friend TableBuilder;
    std::string getSql();
    std::string getName(){
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

    void addColumn(ColumnType column_type, std::string column_name);

    Table build();

private:
    std::vector<std::shared_ptr<Column>> getColumns(){
        return std::move(columns_);
    }
  
    std::string getTableName(){
        return table_name_;
    }

    std::string table_name_;
    std::vector<std::shared_ptr<Column>> columns_;
};

}//namespace st_e
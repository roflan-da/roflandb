#pragma once

#include <utility>

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
        return type_name_;
    }

    virtual std::string Save() = 0;
    //virtual void Load(std::ostream in) = 0;

protected:
    std::string name_;
    std::string type_name_;
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
    explicit Table(TableBuilder builder);
    std::string getSql();
    std::string getName(){
        return name_;
    }
    std::string Save();
    //void Load(std::ostream in);
private:
    std::string name_;
    std::vector<std::shared_ptr<Column>> columns_;
};

class TableBuilder {
public:
    explicit TableBuilder(std::string table_name) :
    table_name_(std::move(table_name)) {}

    void addColumn(std::string column_type, std::string column_name);

    Table build();

    std::string getTableName(){
        return table_name_;
    }

    std::vector<std::shared_ptr<Column>> getColumns(){
        return std::move(columns_);
    }

private:
    std::string table_name_;
    std::vector<std::shared_ptr<Column>> columns_;
};

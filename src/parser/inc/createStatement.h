#pragma once

#include "string"
#include <vector>
#include <memory>

enum column_type{
    INT,
    STRING,
    CHAR,
    TEXT
};

struct column{
    column_type type;
    std::string name;
};

class createStatement{
public:
    explicit createStatement(std::string table_name, column n_columns, ...);

    std::string getTableName();

private:
    std::string table_name_;
    std::vector<std::shared_ptr<column>> columns_;

};

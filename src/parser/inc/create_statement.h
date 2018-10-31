#pragma once

#include "string"
#include <vector>
#include <memory>

namespace prs{

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

class CreateStatement{
public:
    explicit CreateStatement(std::string table_name, column n_columns, ...);

    std::string get_table_name();

private:
    std::string table_name_;
    std::vector<std::shared_ptr<column>> columns_;

};
} //namespace prs
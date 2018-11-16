#pragma once

#include "string"
#include <vector>
#include <memory>
#include <SQL_Statement.h>

namespace cmd{

class CreateStatement : public SQLStatement{
public:
    CreateStatement();

    void execute(st_e::IEngineStorage& storage_engine) override;

    //table_name_ptr_->c_str() for convert ptr to string
    explicit CreateStatement(std::string table_name);

    explicit CreateStatement(std::string table_name,
                             std::shared_ptr<std::vector<std::shared_ptr<st_e::Column>>> n_columns);

    void add_column(std::shared_ptr<st_e::Column> column);
private:
    std::string table_name_;
    std::vector<std::shared_ptr<st_e::Column>> columns_;
};
} //namespace cmd

#pragma once

#include "string"
#include <vector>
#include <memory>
#include <SQL_Statement.h>

namespace cmd{

struct Column{
    Column(ColumnType type, std::string name);

    ColumnType type;
    std::string name;
};

class CreateStatement : public SQLStatement{
public:
    CreateStatement();

    void execute(std::shared_ptr<st_e::IEngineStorage> engine_storage) override;

    explicit CreateStatement(std::string table_name);

    explicit CreateStatement(std::string table_name,
                             std::shared_ptr<std::vector<std::shared_ptr<Column>>> n_columns);

    void add_column(std::shared_ptr<Column> column);

    std::shared_ptr<std::vector<std::shared_ptr<Column>>> get_columns() const;
    std::string get_table_name() const;

private:
    std::string table_name_;
    std::shared_ptr<std::vector<std::shared_ptr<Column>>> columns_;

};
} //namespace prs
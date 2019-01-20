#pragma once

#include <string>
#include <vector>
#include <memory>
#include "sql_statement.h"
#include <query_conditions.h>

namespace cmd {

class UpdateStatement : public SqlStatement {
public:
    UpdateStatement();
    ~UpdateStatement() override = default;

    explicit UpdateStatement(std::string table_name,
                             std::shared_ptr<std::vector<std::pair<std::string, std::string>>> updated_vals,
                             std::shared_ptr<cond::Condition> conditions);

    void execute() override;
private:
    void check_valid() override;
    bool is_condition_valid(const std::shared_ptr<cond::Condition>& condition,
                            st_e::Table::MapOfColumns& columns_names, const st_e::Table::ArrayOfColumns& columns_types);
    std::string table_name_;
    std::shared_ptr<std::vector<std::pair<std::string, std::string>>> updated_vals_;
    std::shared_ptr<cond::Condition> conditions_;
};
} //namespace cmd

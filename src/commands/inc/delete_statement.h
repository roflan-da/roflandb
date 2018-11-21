#pragma once

#include <string>
#include <vector>
#include <memory>
#include "sql_statement.h"
#include <query_conditions.h>

namespace cmd {

class DeleteStatement : public SqlStatement {
public:
    DeleteStatement();
    ~DeleteStatement() override = default;

    explicit DeleteStatement(std::string table_name,
                             std::shared_ptr<cond::QueryConditions> conditions_);

    void execute() override;
private:
    bool is_valid() const override;

    std::string table_name_;
    cond::QueryConditions conditions_;
};
} //namespace cmd

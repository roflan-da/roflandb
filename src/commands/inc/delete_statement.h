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
                             std::shared_ptr<cond::Condition> condition_);

    void execute() override;
private:
    bool is_valid() override;

    std::string table_name_;
    cond::Condition condition_;
};
} //namespace cmd

#pragma once

#include "string"
#include <vector>
#include <memory>
#include <sql_statement.h>
#include <query_conditions.h>
#include "condition.h"

namespace cmd {

enum SelectType{
    ALL,
    VARIABLE
};

class SelectStatement : public SqlStatement {
public:
    SelectStatement();
    ~SelectStatement() override = default;

    void execute() override;

    explicit SelectStatement(const std::string& table_name);

    explicit SelectStatement(std::string table_name,
            std::shared_ptr<std::vector<std::string>> cols_names,
            SelectType type = ALL);

    void add_conditions(std::shared_ptr<cond::QueryConditions> conditions);

private:
    bool is_valid() const override;
    std::string table_name_;
    SelectType type_;
    std::vector<std::string> cols_names_;
    cond::QueryConditions conditions_;
};

} //namespace cmd
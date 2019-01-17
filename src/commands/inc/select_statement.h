#pragma once

#include "string"
#include <vector>
#include <memory>
#include <sql_statement.h>
#include <query_conditions.h>

namespace cmd {


class SelectStatement : public SqlStatement {
public:
    SelectStatement();
    ~SelectStatement() override = default;

    void execute() override;

    explicit SelectStatement(const std::string& table_name);

    explicit SelectStatement(std::string table_name,
            std::shared_ptr<std::vector<std::string>> cols_names, ListType type = ALL);

    void add_conditions(std::shared_ptr<cond::Condition> conditions);

private:
    bool is_condition_valid(const std::shared_ptr<cond::Condition>& condition,
                            st_e::Table::MapOfColumns& columns_names, const st_e::Table::ArrayOfColumns& columns_types);

    void check_valid() override;
    std::string table_name_;
    ListType type_;
    std::vector<std::string> cols_names_;
    std::shared_ptr<cond::Condition> conditions_;
};

} //namespace cmd
#pragma once

#include <string>
#include <vector>
#include <memory>
#include "sql_statement.h"

namespace cmd{
class InsertStatement : public SqlStatement {
public:
    InsertStatement();
    ~InsertStatement() override = default;

    explicit InsertStatement(std::string table_name,
                             std::shared_ptr<std::vector<std::string>> cols_names,
                             std::shared_ptr<std::vector<std::string>> cols_values);

    explicit InsertStatement(std::string table_name,
                             std::shared_ptr<std::vector<std::string>> cols_values);

    void execute() override;
private:
    void check_valid() override;
    friend void SqlStatement::set_message(std::string message);
    st_e::TableRow get_row() const;
    ListType list_type_;

    std::string table_name_;
    std::vector<std::string> columns_names_;
    std::vector<std::string> columns_vals_;
};
} //namespace cmd

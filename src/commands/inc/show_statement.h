#pragma once

#include <string>
#include <vector>
#include <memory>
#include "sql_statement.h"


namespace cmd{
enum ShowType{
    TABLE
};

class ShowStatement : public SqlStatement{
public:
    ShowStatement();
    ~ShowStatement() override = default;

    explicit ShowStatement(ShowType type);
    explicit ShowStatement(ShowType type, std::string name);

    void execute() override;

    ShowType get_type();

    std::string get_name();
private:
    void check_valid() override;
    ShowType type_;
    std::string name_;
};
} //namespace cmd

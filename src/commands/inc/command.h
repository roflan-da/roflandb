#pragma once

// weird interface include
#include "../../storage_engine/inc/i_storage_engine.h"
#include <vector>
#include "SQL_Statement.h"

namespace cmd{

class Command {
public:
    Command();

    explicit Command(std::shared_ptr<cmd::SQLStatement> statement);
    explicit Command(std::shared_ptr<std::vector<std::shared_ptr<cmd::SQLStatement>>> statements);

    void execute(st_e::IEngineStorage& engine_storage);

    bool is_valid() const;
    void is_valid(bool isValid);
    void add_statement(std::shared_ptr<cmd::SQLStatement> statement);

    std::vector<std::shared_ptr<cmd::SQLStatement>> get_statements() { return statements_;};
private:
    bool is_valid_;
    std::vector<std::shared_ptr<cmd::SQLStatement>> statements_;
};

} //namespace cmd

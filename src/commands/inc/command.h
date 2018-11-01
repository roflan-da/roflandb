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

    virtual void execute(std::shared_ptr<st_e::IEngineStorage> engine_storage) {};

    bool isValid() const;
    void isValid(bool isValid);
    std::shared_ptr<cmd::SQLStatement> getStatement(int index) const;
private:
    bool isValid_;
    std::vector<std::shared_ptr<cmd::SQLStatement>> statements_;
};

} //namespace cmd

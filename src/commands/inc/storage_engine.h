#pragma once

// weird interface include
#include "../../storage_engine/inc/i_storage_engine.h"
#include <vector>
#include "SQL_Statement.h"

namespace cdm{

class Command {
public:
    Command();

    explicit Command(cmd::SQLStatement* statement);

    virtual void execute(st_e::IEngineStorage engine_storage) = 0;

    bool isValid() const;
    long long int getStatemensSize() const;
    void addStatement(cmd::SQLStatement* statement);
    std::shared_ptr<cmd::SQLStatement> getStatement(int index) const;
private:
    bool isValid_;
    std::vector<std::shared_ptr<cmd::SQLStatement>> statements_;
};

} //namespace cmd

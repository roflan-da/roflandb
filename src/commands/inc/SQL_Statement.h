#pragma once

#include "../../storage_engine/inc/i_storage_engine.h"

namespace cmd{
enum StatementType{
    NONE,
    CREATE_TABLE,
    SHOW,
    DROP,
    SELECT,
    INSERT
};

class SQLStatement {
public:
    SQLStatement();
    explicit SQLStatement(StatementType type);

    std::string get_message();
    void set_message(std::string message);

    virtual void execute(st_e::IEngineStorage& engine_storage) = 0;
private:
    std::string message_;
    StatementType type_;
};

} //namespace cmnd

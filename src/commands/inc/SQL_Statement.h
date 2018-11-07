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

    virtual void execute(std::shared_ptr<st_e::IEngineStorage> engine_storage){};

    StatementType type() const;
private:
    StatementType type_;
};

} //namespace cmnd

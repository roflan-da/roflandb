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
    virtual ~SQLStatement() = default;
    explicit SQLStatement(StatementType type);

    std::string get_message();
    void set_message(std::string message);

    virtual void execute(st_e::IEngineStorage& storage_engine) = 0;
    virtual bool is_valid(st_e::IEngineStorage& storage_engine) = 0;

    StatementType type() { return type_; }
    void type(StatementType type) { type_ = type; }
private:
    std::string message_;
    StatementType type_;
};

} //namespace cmnd

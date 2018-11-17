#pragma once

#include <string>
#include <storage_engine.h>

namespace cmd {

enum StatementType{
    NONE,
    CREATE_TABLE,
    SHOW,
    DROP,
    SELECT,
    INSERT
};

class SqlStatement {
public:
    SqlStatement();
    explicit SqlStatement(StatementType type);

    std::string get_message();
    void set_message(std::string message);

    virtual void execute(st_e::StorageEngine& engine_storage) = 0;

private:
   // virtual bool is_valid(st_e::StorageEngine& engine_storage) = 0;
    std::string message_;
    StatementType type_;
};

} //namespace cmnd

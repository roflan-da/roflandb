#pragma once

#include <string>
#include "storage_engine.h"

#ifdef SET_PRIVATE_AS_PUBLIC
#define PRIVATE public
#else
#define PRIVATE private
#endif

namespace cmd {

enum StatementType{
    NONE,
    CREATE_TABLE,
    SHOW,
    DROP,
    SELECT,
    INSERT,
    DELETE
};

enum ListType{
    VARIABLE,
    ALL
};

class SqlStatement {
public:
    SqlStatement();
    explicit SqlStatement(StatementType type);
    virtual ~SqlStatement() = default;

    std::string get_message();
    void set_message(std::string message);

    virtual void execute() = 0;

private:
    virtual bool is_valid() = 0;
    std::string message_;
    StatementType type_;
};

} //namespace cmd

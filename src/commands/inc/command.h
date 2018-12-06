#pragma once

// weird interface include
#include <vector>
#include "sql_statement.h"

#ifdef SET_PRIVATE_AS_PUBLIC
#define PRIVATE public
#else
#define PRIVATE private
#endif

namespace cmd{
class Command {
public:
    Command() = default;

    explicit Command(std::shared_ptr<std::vector<std::shared_ptr<cmd::SqlStatement>>> statements);

    void execute();
    std::string get_messages();
PRIVATE:
    std::vector<std::shared_ptr<cmd::SqlStatement>> statements_;
};
} //namespace cmd

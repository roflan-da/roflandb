#pragma once

// weird interface include
#include "../../storage_engine/inc/i_storage_engine.h"
#include <vector>
#include "sql_statement.h"

namespace cmd{

    class Command {
    public:
        Command() = default;

        explicit Command(std::shared_ptr<std::vector<std::shared_ptr<cmd::SqlStatement>>> statements);

        void execute(st_e::IEngineStorage& engine_storage);
        std::string get_messages();
    private:
        std::vector<std::shared_ptr<cmd::SqlStatement>> statements_;
    };

} //namespace cmd

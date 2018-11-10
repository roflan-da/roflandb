#include <utility>

#include <command.h>
#include "iostream"

void cmd::Command::execute(st_e::IEngineStorage& engine_storage) {
    for (const auto& statement : statements_){
        statement->execute(engine_storage);
    }
}

cmd::Command::Command(std::shared_ptr<std::vector<std::shared_ptr<cmd::SQLStatement>>> statements) {
    statements_ = *statements.get();
}

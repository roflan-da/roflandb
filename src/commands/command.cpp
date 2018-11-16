#include <utility>

#include <command.h>
#include "iostream"

void cmd::Command::execute(st_e::IEngineStorage& storage_engine) {
    for (const auto& statement : statements_){
        statement->execute(storage_engine);
    }
}

cmd::Command::Command(std::shared_ptr<std::vector<std::shared_ptr<cmd::SQLStatement>>> statements) {
    statements_ = *statements.get();
}

std::string cmd::Command::get_messages() {
    std::string result;
    for (const auto& statement : statements_) {
        result += statement->get_message() + '\n';
    }
    return result;
}

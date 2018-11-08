#include <utility>

#include <command.h>
#include "iostream"

cmd::Command::Command() : isValid_(false){};

cmd::Command::Command(std::shared_ptr<cmd::SQLStatement> statement) : isValid_(false) {
    addStatement(std::move(statement));
};

bool cmd::Command::isValid() const {
    return isValid_;
}

void cmd::Command::addStatement(std::shared_ptr<cmd::SQLStatement> statement) {
    statements_.emplace_back(statement);
}

void cmd::Command::isValid(bool isValid) {
    isValid_ = isValid;
}

void cmd::Command::execute(st_e::IEngineStorage& engine_storage) {
    for (const auto& statement : statements_){
        statement->execute(engine_storage);
    }
}

cmd::Command::Command(std::shared_ptr<std::vector<std::shared_ptr<cmd::SQLStatement>>> statements) {
    statements_ = *statements.get();
}

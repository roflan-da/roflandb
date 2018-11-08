#include <utility>

#include <command.h>
#include "iostream"

cmd::Command::Command() : is_valid_(false) {}

cmd::Command::Command(std::shared_ptr<cmd::SQLStatement> statement) : is_valid_(false) {
    add_statement(std::move(statement));
}

bool cmd::Command::is_valid() const {
    return is_valid_;
}

void cmd::Command::add_statement(std::shared_ptr<cmd::SQLStatement> statement) {
    statements_.emplace_back(statement);
}

void cmd::Command::is_valid(bool isValid) {
    is_valid_ = isValid;
}

void cmd::Command::execute(st_e::IEngineStorage& engine_storage) {
    for (const auto& statement : statements_){
        statement->execute(engine_storage);
    }
}

cmd::Command::Command(std::shared_ptr<std::vector<std::shared_ptr<cmd::SQLStatement>>> statements) {
    statements_ = *statements.get();
}

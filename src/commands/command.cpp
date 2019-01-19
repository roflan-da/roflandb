#include <utility>

#include <command.h>
#include <storage_engine_exceptions.h>
#include "iostream"


void cmd::Command::execute() {
    for (const auto& statement : statements_){
        try{
            statement->execute();
        } catch(st_e::RoflanException& exc){
            statement->set_message(exc.get_message());
        }
    }
}

cmd::Command::Command(std::shared_ptr<std::vector<std::shared_ptr<cmd::SqlStatement>>> statements) {
    statements_ = *statements.get();
}

std::string cmd::Command::get_messages() {
    std::string result;
    for (const auto& statement : statements_) {
        result += statement->get_message() + '\n';
    }
    return result;
}
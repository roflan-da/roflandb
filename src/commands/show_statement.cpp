#include <utility>
#include <show_statement.h>

cmd::ShowStatement::ShowStatement() : type_(cmd::TABLE) {}

cmd::ShowStatement::ShowStatement(cmd::ShowType type) : type_(type) {}

void cmd::ShowStatement::execute(st_e::IEngineStorage& storage_engine) {

}

cmd::ShowType cmd::ShowStatement::get_type() {
    return type_;
}

std::string cmd::ShowStatement::get_name() {
    return name_;
}

cmd::ShowStatement::ShowStatement(cmd::ShowType type, std::string name) : type_(type), name_(name){}



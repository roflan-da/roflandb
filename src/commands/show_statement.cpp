#include <utility>
#include <show_statement.h>

cmd::ShowStatement::ShowStatement() : type_(cmd::TABLE){};

cmd::ShowStatement::ShowStatement(cmd::ShowType type) : type_(type){};

void cmd::ShowStatement::execute(std::shared_ptr<st_e::IEngineStorage> engine_storage) {

}

cmd::ShowType cmd::ShowStatement::get_type() {
    return type_;
}

std::string cmd::ShowStatement::get_name() {
    return name_;
}



#include <utility>
#include "show_statement.h"
#include "storage_engine_exceptions.h"


cmd::ShowStatement::ShowStatement() : SqlStatement(SHOW), type_(cmd::TABLE) {}

cmd::ShowStatement::ShowStatement(cmd::ShowType type) : SqlStatement(SHOW), type_(type) {}

void cmd::ShowStatement::execute() {
    auto table = st_e::StorageEngine::get_instance().get_table_by_name(name_);
    std::cout << table.get_sql() << std::endl;
}

cmd::ShowType cmd::ShowStatement::get_type() {
    return type_;
}

std::string cmd::ShowStatement::get_name() {
    return name_;
}

cmd::ShowStatement::ShowStatement(cmd::ShowType type, std::string name) : type_(type), name_(name){}

bool cmd::ShowStatement::is_valid() {
    try {
        auto table = st_e::StorageEngine::get_instance().get_table_by_name(name_);
    }
    catch (st_e::TableNotExistException &e) {
        return false;
    }
}
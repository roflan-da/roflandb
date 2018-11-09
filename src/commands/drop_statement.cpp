#include <drop_statement.h>

void cmd::DropStatement::execute(st_e::IEngineStorage &storage_engine) {
    switch (type_){
        case DROP_TABLE :
            storage_engine.delete_table(name_);
            break;
        case DROP_DATABASE :
            //storage_engine.delete_database(name_);
            break;
        default:
            break;
    }
}

cmd::DropStatement::DropStatement(std::string table_name) : type_(DROP_TABLE), name_(table_name){}

cmd::DropStatement::DropStatement(cmd::DropType type, std::string name) : type_(type), name_(name){}

cmd::DropType cmd::DropStatement::get_type() const {
    return type_;
}

std::string cmd::DropStatement::get_name() const {
    return name_;
}


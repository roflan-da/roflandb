#include "drop_statement.h"
#include "storage_engine_exceptions.h"

cmd::DropStatement::DropStatement() : SqlStatement(DROP) {}

void cmd::DropStatement::execute() {
    if (!is_valid()){
        //TODO: Exception or message
        return;
    }
    switch (type_){
        case DROP_TABLE :
            st_e::StorageEngine::get_instance().delete_table(name_);
            break;
        case DROP_DATABASE :
            //storage_engine.delete_database(name_);
            break;
        default:
            break;
    }
}

cmd::DropStatement::DropStatement(std::string table_name) : SqlStatement(DROP), type_(DROP_TABLE), name_(table_name){}

cmd::DropStatement::DropStatement(cmd::DropType type, std::string name) : SqlStatement(DROP), type_(type), name_(name){}

cmd::DropType cmd::DropStatement::get_type() const {
    return type_;
}

std::string cmd::DropStatement::get_name() const {
    return name_;
}

bool cmd::DropStatement::is_valid() {
    if (type_ == DROP_TABLE) {
        try {
            auto table = st_e::StorageEngine::get_instance().get_table_by_name(name_);
        }
        catch (st_e::TableNotExistException &e) {
            return false;
        }
    }
    else{
        return false;
    }
    return true;
}
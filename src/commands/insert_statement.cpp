#include <insert_statement.h>


cmd::InsertStatement::InsertStatement() {}

cmd::InsertStatement::InsertStatement(std::string table_name) : table_name_(table_name){

}

std::string cmd::InsertStatement::get_table_name() {
    return table_name_;
}

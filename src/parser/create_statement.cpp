#include "create_statement.h"

prs::CreateStatement::CreateStatement(std::string table_name, column n_columns, ...) {

}

std::string prs::CreateStatement::get_table_name() {
    return table_name_;
}

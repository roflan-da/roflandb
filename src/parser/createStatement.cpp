
#include <createStatement.h>

#include "inc/createStatement.h"


createStatement::createStatement(std::string table_name, column n_columns, ...) {

}

std::string createStatement::getTableName() {
    return table_name_;
}

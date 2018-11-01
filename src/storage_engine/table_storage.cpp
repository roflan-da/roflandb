#include "table_storage.h"

void TableStorage::addTable(std::shared_ptr<Table> table) {
    tables_[table->getName()] = table;
}

void TableStorage::deleteTable(std::string table_name) {
    auto it = tables_.find(table_name);
    if(it != tables_.end()){
        tables_.erase(it);
    }
}

std::map<std::string, std::shared_ptr<Table>>::iterator TableStorage::findTable(std::string table_name) {
    return tables_.find(table_name);
}
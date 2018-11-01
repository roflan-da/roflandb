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

std::string TableStorage::Save() {
    std::string tables_string;
    tables_string = std::to_string(tables_.size()) + " ";
    for (auto it = tables_.begin(); it != tables_.end(); it++) {
        tables_string += it->second->Save();
    }
    return tables_string;
}

void TableStorage::Load(std::string tables_string) {

}
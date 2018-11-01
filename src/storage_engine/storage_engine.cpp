#include "storage_engine.h"

namespace st_e {

    void StorageEngine::addTable(std::shared_ptr<Table> table) {
        tables_[table->getName()] = table;
    }

    void StorageEngine::deleteTable(std::string table_name) {
        auto it = tables_.find(table_name);
        if (it != tables_.end()) {
            tables_.erase(it);
        }
    }

    std::map<std::string, std::shared_ptr<Table>>::iterator StorageEngine::findTable(std::string table_name) {
        return tables_.find(table_name);
    }

    std::string StorageEngine::Save() {
        std::string tables_string;
        tables_string = std::to_string(tables_.size()) + " ";
        for (auto it = tables_.begin(); it != tables_.end(); it++) {
            tables_string += it->second->Save();
        }
        return tables_string;
    }

    void StorageEngine::Load(std::string tables_string) {

    }

}//namespace st_e
#include "table.h"
#include <string>
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

    std::shared_ptr<Table> st_e::StorageEngine::getTableByName(std::string table_name) {
        return tables_.find(table_name)->second;
    }

    std::string StorageEngine::Save() {
        std::string tables_string;
        tables_string = std::to_string(tables_.size()) + " ";
        for (auto it = tables_.begin(); it != tables_.end(); it++) {
            tables_string += it->second->Save();
        }
        return tables_string;
    }

    void StorageEngine::Load(std::ifstream &in) {
        int count;
        in >> count;
        for (int i = 0; i < count; i++){
            std::string table_name;
            in >> table_name;
            TableBuilder tableBuilder(table_name);
            int columns_count;
            in >> columns_count;
            for (int j = 0; j < columns_count; j++){
                std::string type, column_name;
                in >> column_name >> type;
                tableBuilder.addColumn(type, column_name);
            }
            Table table = tableBuilder.build();
            addTable(std::make_shared<Table>(table));
        }
    }

}//namespace st_e
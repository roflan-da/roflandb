#include "table.h"
#include <string>
#include "storage_engine.h"

namespace st_e {

    void StorageEngine::add_table(std::shared_ptr<Table> table) {
        tables_[table->get_name()] = table;
    }

    void StorageEngine::delete_table(std::string table_name) {
        auto it = tables_.find(table_name);
        if (it != tables_.end()) {
            tables_.erase(it);
        }
    }

    std::shared_ptr<Table> st_e::StorageEngine::get_table_by_name(std::string table_name) {
        return tables_.find(table_name)->second;
    }

    void StorageEngine::save() {
        std::string tables_string;
        tables_string = std::to_string(tables_.size()) + " ";
        for (auto it = tables_.begin(); it != tables_.end(); it++) {
            tables_string += it->second->Save();
        }
        std::ofstream out("My_db.txt");
        out << tables_string;
    }

    void StorageEngine::load() {
        std::ifstream in("My_db.txt");
        int count;
        in >> count;
        for (int i = 0; i < count; i++){
            std::string table_name;
            in >> table_name;
            TableBuilder tableBuilder(table_name);
            int columns_count;
            in >> columns_count;
            for (int j = 0; j < columns_count; j++){
                std::string column_name;
                int type;
                in >> column_name >> type;
                tableBuilder.add_column(static_cast<ColumnType>(type), column_name);
            }
            Table table = tableBuilder.build();
            add_table(std::make_shared<Table>(table));
        }
    }

}//namespace st_e
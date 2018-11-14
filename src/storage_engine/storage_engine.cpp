#include "storage_engine.h"
#include <string>
#include <storage_engine.h>


namespace st_e {

    StorageEngine::StorageEngine() {
        load();
    }

    void StorageEngine::add_table(std::shared_ptr<Table> table) {
        tables_[table->get_name()] = table;
    }

    bool StorageEngine::delete_table(std::string table_name) {
        auto it = tables_.find(table_name);
        if (it != tables_.end()) {
            tables_.erase(it);
            return true;
        }
        return false;
    }

    std::shared_ptr<Table> StorageEngine::get_table_by_name(std::string table_name) {
        return tables_.find(table_name)->second;
    }

    void StorageEngine::save() {
        std::string tables_string;
        tables_string = std::to_string(tables_.size()) + " ";
        for (auto it = tables_.begin(); it != tables_.end(); it++) {
            tables_string += it->second->to_string();
        }
        std::ofstream out("My_db.txt");
        out << tables_string;
    }

    void StorageEngine::load() {
        std::ifstream in("My_db.txt");
        size_t count;
        in >> count;
        for (size_t i = 0; i < count; i++){
            std::string table_name;
            in >> table_name;
            TableBuilder tableBuilder(table_name);
            size_t columns_count;
            in >> columns_count;
            std::vector<std::shared_ptr<Column>> columns;
            for (size_t j = 0; j < columns_count; j++){
                std::string column_name;
                int type;
                in >> type >> column_name;
                columns.emplace_back(std::make_shared<Column>(static_cast<ColumnType>(type), column_name));
            }
            tableBuilder.set_columns(columns);
            auto table = tableBuilder.build();
            size_t rows_count;
            in >> rows_count;
            for (size_t i = 0; i < rows_count; i++){
                std::vector<std::pair<ColumnType, std::string>> row;
                for (size_t j = 0; j < columns_count; j++) {
                    std::string data;
                    in >> data;
                    row.emplace_back(columns[j]->type, data);
                }
                table->insert(row);
            }
            add_table(table);
        }
    }

    void StorageEngine::insert(std::string table_name, std::vector<std::pair<std::string, std::string>> raw) {
        std::shared_ptr<Table> table = get_table_by_name(std::move(table_name));   //добавить проверку на существование
        table->insert(std::move(raw));
        save();
    }

    SelectAnswer StorageEngine::select(std::string table_name, std::vector<std::string> columns_names) {
        return tables_.find(table_name)->second->select(columns_names);  //добавить проверку на существование
    }

    SelectAnswer StorageEngine::select_all(std::string table_name) {
        return tables_.find(table_name)->second->select_all();  //добавить проверку на существование
    }

}//namespace st_e
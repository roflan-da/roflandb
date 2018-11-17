#include <string>
#include "storage_engine.h"

namespace st_e {

StorageEngine::StorageEngine() {
    load();
}

void StorageEngine::add_table(TablePtr table) {
    tables_[table->get_name()] = table;
}

bool StorageEngine::delete_table(std::string table_name) {
    std::transform(table_name.begin(), table_name.end(), table_name.begin(), tolower);
    auto it = tables_.find(table_name);
    if (it != tables_.end()) {
        tables_.erase(it);
        return true;
    }
    return false;
}

StorageEngine::TablePtr StorageEngine::get_table_by_name(std::string table_name) {
    std::transform(table_name.begin(), table_name.end(), table_name.begin(), tolower);
    return tables_.find(table_name)->second;
}

void StorageEngine::insert(std::string table_name, std::vector<std::pair<std::string, std::string>> row) {
    auto table = get_table_by_name(std::move(table_name));   //добавить проверку на существование
    table->insert(std::move(row));
    save();
}

SelectAnswer StorageEngine::select(std::string table_name, std::vector<std::string> columns_names) {
    std::transform(table_name.begin(), table_name.end(), table_name.begin(), tolower);
    return tables_.find(table_name)->second->select(columns_names);  //добавить проверку на существование
}

SelectAnswer StorageEngine::select_all(std::string table_name) {
    std::transform(table_name.begin(), table_name.end(), table_name.begin(), tolower);
    return tables_.find(table_name)->second->select_all();  //добавить проверку на существование
}

void StorageEngine::save() {
    std::string tables_string;
    tables_string = std::to_string(tables_.size()) + " ";
    for (const auto& table : tables_) {
        tables_string += table.second->to_string();
    }
    std::ofstream out("My_db.txt");
    out << tables_string;
}

void StorageEngine::load() {
    std::ifstream in("My_db.txt");
    if (!in.is_open())
        return;

    size_t count;
    in >> count;
    for (size_t i = 0; i < count; i++) {
        std::string table_name;
        in >> table_name;
        TableBuilder tableBuilder(table_name);
        size_t columns_count;
        in >> columns_count;
        std::vector<std::shared_ptr<Column>> columns;
        for (size_t j = 0; j < columns_count; j++) {
            std::string column_name;
            int type;
            in >> type >> column_name;
            columns.emplace_back(std::make_shared<Column>(static_cast<ColumnType>(type), column_name));
        }
        tableBuilder.set_columns(columns);
        auto table = tableBuilder.build();
        size_t rows_count;
        in >> rows_count;
        for (size_t i = 0; i < rows_count; i++) {
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

}//namespace st_e
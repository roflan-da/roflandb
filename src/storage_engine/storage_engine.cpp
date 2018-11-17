#include <string>
#include "storage_engine.h"

namespace st_e {

void StorageEngine::add_table(const Table& table) {
    tables_.save_table(table);
}

//bool StorageEngine::delete_table(std::string table_name) {
//    auto it = tables_.find(table_name);
//    if (it != tables_.end()) {
//        tables_.erase(it);
//        return true;
//    }
//    return false;
//}

// Todo: remove
//StorageEngine::TablePtr StorageEngine::get_table_by_name(std::string table_name) {
//    return tables_.find(table_name)->second;
//}

//void StorageEngine::insert(std::string table_name, std::vector<std::pair<std::string, std::string>> row) {
//    auto table = get_table_by_name(std::move(table_name));   //добавить проверку на существование
//    table->insert(std::move(row));
//    save();
//}

//SelectAnswer StorageEngine::select(std::string table_name, std::vector<std::string> columns_names) {
//    return tables_.find(table_name)->second->select(columns_names);  //добавить проверку на существование
//}
//
//SelectAnswer StorageEngine::select_all(std::string table_name) {
//    return tables_.find(table_name)->second->select_all();  //добавить проверку на существование
//}


}//namespace st_e
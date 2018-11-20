#include <string>

#include "storage_engine.h"
#include "table_chunk.h"

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


const st_e::Table& StorageEngine::get_table_by_name(const std::string& table_name) {
    return tables_.get_table(table_name);
}

StorageEngine &StorageEngine::get_instance() {
    static StorageEngine instance;
    return instance;
}

void StorageEngine::insert(const std::string& table_name, const std::vector<TableRow>& rows) {
    auto columns = get_table_by_name(table_name).get_columns();

    std::vector<char> record_buffer;

    // first byte is internal value.
    record_buffer.resize(sizeof(uint32_t));
    uint32_t internal_flag = 0;
    std::memcpy(record_buffer.data(), &internal_flag, sizeof(uint32_t));

    for (const auto& row : rows) {
        //todo: add more types
        for (const auto& cell : row.get_cells()) {
            uint32_t value = dynamic_cast<const IntegerTableCell&>(cell).get_value();
            auto first_unused_byte = record_buffer.size();
            record_buffer.resize(record_buffer.size() + sizeof(uint32_t));
            std::memcpy(record_buffer.data() + first_unused_byte, &value, sizeof(uint32_t));
        }
    }

//    std::string res(record_buffer.data());
//
//    int a = 2;
}

void StorageEngine::load_last_block(const std::string& table_name){
    auto table = tables_.get_table(table_name);
    auto data_file_path = table.get_data_file_path();

    std::fstream data_file;
    data_file.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    data_file.open(table.get_data_file_path().string(), std::ios::binary);

    uint32_t first_existing_block;
    data_file.read(reinterpret_cast<char*>(&first_existing_block), sizeof(uint32_t));
    if (first_existing_block == 0) {

    }
}


//SelectAnswer StorageEngine::select(std::string table_name, std::vector<std::string> columns_names) {
//    return tables_.find(table_name)->second->select(columns_names);  //добавить проверку на существование
//}
//
//SelectAnswer StorageEngine::select_all(std::string table_name) {
//    return tables_.find(table_name)->second->select_all();  //добавить проверку на существование
//}

}//namespace st_e
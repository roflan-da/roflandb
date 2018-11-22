#include <string>
#include <storage_engine.h>
#include <table_chunk.h>
#include <configuration.h>
#include <storage_engine_exceptions.h>

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

void StorageEngine::insert(const std::string& table_name, const TableRow& row) {
    const auto& table = get_table_by_name(table_name);
    const auto& columns = table.get_columns();

    std::vector<char> record_buffer;

    record_buffer.resize(sizeof(char));
    // first byte is internal value. Value of 0 means not deleted record
    char internal_flag = 0;
    std::memcpy(record_buffer.data(), &internal_flag, sizeof(char));

    for (const auto& cell : row.get_cells()) {
        //todo: add more types
        cell->push_into_buffer(record_buffer);
    }

    auto last_block = get_last_block(table_name);

    if (last_block.get_free_space() < record_buffer.size()) {
        // create new
        return;
    }

    append_record_to_block(record_buffer, last_block, table);
}

DataBlock StorageEngine::get_last_block(const std::string& table_name) {
    auto table = tables_.get_table(table_name);
    auto data_file_path = table.get_data_file_path();

    std::fstream data_file;

    auto  t = table.get_data_file_path().string();
    data_file.open(table.get_data_file_path().string(), std::fstream::binary | std::fstream::in | std::fstream::out | std::fstream::app);

    if (!data_file.is_open()) {
        throw TableNotExistException(table.get_name());
    }

    uint32_t first_block_ptr;
    data_file.read(reinterpret_cast<char*>(&first_block_ptr), sizeof(uint32_t));

    // if it is first insert and we have no block created.
    if (first_block_ptr == 0) {
        DataBlock new_data_block(0, 0, DATA_FILE_HEADER_SIZE);
        data_file.seekp(std::ios_base::end);
        auto block_binary = new_data_block.get_binary_representation();
        data_file.write(block_binary.data(), block_binary.size());

        return new_data_block;
    }

    uint32_t prev_block_ptr = 0;
    auto next_block_ptr = first_block_ptr;
    long long current_file_offset = 0;

    do {
        current_file_offset = DATA_FILE_HEADER_SIZE + next_block_ptr;
        data_file.seekg(current_file_offset);
        data_file.read(reinterpret_cast<char*>(&prev_block_ptr), sizeof(uint32_t));
        data_file.read(reinterpret_cast<char*>(&next_block_ptr), sizeof(uint32_t));

    } while (next_block_ptr);

    return DataBlock(prev_block_ptr, next_block_ptr, current_file_offset);
}

void StorageEngine::append_record_to_block(const std::vector<char>& buffer, const DataBlock& block, const Table& table) {
    std::fstream data_file(table.get_data_file_path().string(), std::fstream::binary | std::fstream::in | std::fstream::out);
    data_file.seekp(0, std::ios::end);

    if (!data_file.is_open()) {
        throw  TableNotExistException(table.get_name());
    }

    long long free_offset_value_offset = block.get_file_offset() + 12; // 12 because free_offset is 4th uint32_t
    data_file.seekg(block.get_file_offset() + block.get_free_offset());
    data_file.write(buffer.data(), buffer.size());

    data_file.seekp(free_offset_value_offset);
    auto new_free_offset_value = static_cast<uint32_t>(block.get_free_offset() + buffer.size());
    data_file.write(reinterpret_cast<const char*>(&new_free_offset_value), sizeof(uint32_t));
    data_file.close();
}


//SelectAnswer StorageEngine::select(std::string table_name, std::vector<std::string> columns_names) {
//    return tables_.find(table_name)->second->select(columns_names);  //добавить проверку на существование
//}
//
//SelectAnswer StorageEngine::select_all(std::string table_name) {
//    return tables_.find(table_name)->second->select_all();  //добавить проверку на существование
//}

}//namespace st_e
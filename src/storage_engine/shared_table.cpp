#include <fstream>
#include <algorithm>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <data_block.h>
#include <shared_table.h>


#include "shared_table.h"
#include "configuration.h"
#include "storage_engine_exceptions.h"

namespace fs = boost::filesystem;

namespace st_e {

SharedTable& SharedTable::get_instance() {
    static SharedTable instance;
    return instance;
}

const Table& SharedTable::get_table(const std::string& name) {
    auto table = cached_tables_.find(name);
    if (table != cached_tables_.end()) {
        return table->second;
    }

    return load_table(name);
}

Table& SharedTable::load_table(const std::string& table_name) {
    auto invariant_table_name = boost::to_lower_copy(table_name);
    auto meta_data_file_path = st_e::Table::get_metadata_file_path(table_name);

    if (!fs::exists(meta_data_file_path)) {
        throw TableNotExistException(table_name);
    }

    std::ifstream data_file;
    data_file.exceptions(std::ifstream::badbit);
    data_file.open(meta_data_file_path.string());

    TableBuilder table_builder(invariant_table_name);

    std::string tmp_string_type;
    std::string tmp_col_name;
    st_e::Column::Type tmp_col_type;

    while (!data_file.eof()) {
        data_file >> tmp_string_type >> tmp_col_name >> std::skipws;

        //skip new lines
        while(data_file.peek() == '\n' || data_file.peek() == '\r') {
            data_file.get();
        }

        tmp_col_type = Column::get_type_from_string(tmp_string_type);
        table_builder.add_column(tmp_col_type, tmp_col_name);
    }
    data_file.close();
    table_locks.insert_or_assign(invariant_table_name, false);
    return cached_tables_.insert_or_assign(invariant_table_name, table_builder.build()).first->second;
}

void SharedTable::save_table(const Table& table) {
    // first save to disk, then to RAM
    save_to_disk(table);
    cached_tables_.insert_or_assign(table.get_name(), table);
}

void SharedTable::save_to_disk(const Table& table) const {
    auto data_dir = st_e::Table::get_metadata_file_path(table.get_name()).parent_path();
    // create metadata file
    auto metadata_file_path = st_e::Table::get_metadata_file_path(table.get_name());
    // Todo: try-catch
    if (!fs::exists(data_dir)) {
        fs::create_directories(data_dir);
    }

    std::ofstream metadata_file;
    metadata_file.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    metadata_file.open(metadata_file_path.string());

    for (const auto& column : table.get_ordered_columns()) {
        metadata_file << column.get_type_string() << " " << column.name << '\n';
    }
    metadata_file.close();

    // create data file
    std::ofstream data_file;
    data_file.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    data_file.open(st_e::Table::get_data_file_path(table.get_name()).string(), std::ios::binary);

    // see <data_block.h> for details
    // set prev and next blocks to 0
    uint32_t no_block_pointer = 0;
    uint32_t block_counter = 1;
    data_file.write(reinterpret_cast<char*>(&block_counter), sizeof(uint32_t));
    data_file.write(reinterpret_cast<char*>(&block_counter), sizeof(uint32_t));
    data_file.write(reinterpret_cast<char*>(&no_block_pointer), sizeof(uint32_t));
    data_file.write(reinterpret_cast<char*>(&block_counter), sizeof(uint32_t));

    DataBlock new_data_block(0, 0, 0, 1);// TODO::Вставить нормальную генерацию номеров(тут это мб и не обязательно)
    auto block_binary = new_data_block.get_binary_representation();
    data_file.write(block_binary.data(), block_binary.size());

    data_file.close();
}

void SharedTable::delete_table(const std::string& table_name) {
    auto data_dir = st_e::Table::get_metadata_file_path(table_name).parent_path();
    boost::filesystem::remove_all(data_dir);
    cached_tables_.erase(table_name);
}

} // namespace st_e

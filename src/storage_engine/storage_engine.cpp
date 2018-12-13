#include <string>
#include <storage_engine.h>
#include <table_chunk.h>
#include <configuration.h>
#include <storage_engine_exceptions.h>
#include <row_check.h>

namespace st_e {

void StorageEngine::add_table(const Table& table) {
    tables_.save_table(table);
}

void StorageEngine::delete_table(const std::string& table_name) {
    tables_.delete_table(table_name);
}

const st_e::Table& StorageEngine::get_table_by_name(const std::string& table_name) {
    return tables_.get_table(table_name);
}

StorageEngine &StorageEngine::get_instance() {
    static StorageEngine instance;
    return instance;
}

void StorageEngine::insert(const std::string& table_name, const TableRow& row) {
    const auto& table = get_table_by_name(table_name);

    std::vector<char> record_buffer;

    row.push_binary(record_buffer);

    auto last_block = get_last_block(table_name);

    if (last_block.get_free_space() < record_buffer.size()) {
        last_block = append_new_block(table_name, last_block);
    }

    append_record_to_block(record_buffer, last_block, table);
}

DataBlock StorageEngine::get_block(const std::string& table_name, uint32_t block_number) {
    auto table = tables_.get_table(table_name);
    std::fstream data_file;
    data_file.open(table.get_data_file_path().string(), std::fstream::binary | std::fstream::in | std::fstream::out);

    if (!data_file.is_open()) {
        throw TableNotExistException(table.get_name());
    }

    uint32_t next_block_ptr;
    uint32_t prev_block_ptr;
    uint32_t cur_block_ptr;
    uint32_t free_offset;
    uint32_t data_start;

    // Low level section ahead. Please fasten your seatbelts and don't touch anything.
    long long current_file_offset = DATA_FILE_HEADER_SIZE + (block_number - 1) * DATA_BLOCK_SIZE;
    data_file.seekg(current_file_offset);
    data_file.read(reinterpret_cast<char*>(&prev_block_ptr), sizeof(uint32_t));
    data_file.read(reinterpret_cast<char*>(&next_block_ptr), sizeof(uint32_t));
    data_file.read(reinterpret_cast<char*>(&data_start),     sizeof(uint32_t));
    data_file.read(reinterpret_cast<char*>(&free_offset),    sizeof(uint32_t));
    data_file.read(reinterpret_cast<char*>(&cur_block_ptr),  sizeof(uint32_t));

    return DataBlock(prev_block_ptr, next_block_ptr, data_start, free_offset, cur_block_ptr);
}

DataBlock StorageEngine::get_first_block(const std::string& table_name) {
    return get_block(table_name, 1);
}

DataBlock StorageEngine::get_last_block(const std::string& table_name) {
    auto table = tables_.get_table(table_name);

    std::fstream data_file;
    data_file.open(table.get_data_file_path().string(), std::fstream::binary | std::fstream::in | std::fstream::out);

    if (!data_file.is_open()) {
        throw TableNotExistException(table.get_name());
    }

    uint32_t last_block;
    data_file.seekg(4);
    data_file.read(reinterpret_cast<char*>(&last_block), sizeof(uint32_t));
    return get_block(table_name, last_block);
}

void StorageEngine::append_record_to_block(const std::vector<char>& buffer, const DataBlock& block, const Table& table) {
    std::fstream data_file(table.get_data_file_path().string(), std::fstream::binary | std::fstream::in | std::fstream::out);

    if (!data_file.is_open()) {
        throw  TableNotExistException(table.get_name());
    }
    // Low level section ahead. Please fasten your seatbelts and don't touch anything.
    long long free_offset_value_offset = block.get_file_offset() + 12; // 12 because free_offset is 4th uint32_t
    data_file.seekp(block.get_file_offset() + block.get_free_offset());
    data_file.write(buffer.data(), buffer.size());

    data_file.seekp(free_offset_value_offset);
    auto new_free_offset_value = static_cast<uint32_t>(block.get_free_offset() + buffer.size());
    data_file.write(reinterpret_cast<const char*>(&new_free_offset_value), sizeof(uint32_t));
    data_file.close();
}

DataBlock StorageEngine::append_new_block(const std::string& table_name, const DataBlock& last_block) {
    auto table = tables_.get_table(table_name);
    auto data_file_path = table.get_data_file_path();

    std::fstream data_file;
    // Low level section ahead. Please fasten your seatbelts and don't touch anything.
    data_file.open(table.get_data_file_path().string(), std::fstream::binary | std::fstream::in | std::fstream::out);

    if (!data_file.is_open()) {
        throw TableNotExistException(table.get_name());
    }

    // FILL PREV BLOCK WITH ZEROES TO KEEP RIGHT ALIGN
    data_file.seekp(last_block.get_file_offset() + last_block.get_free_offset());
    char zero = 0;
    for (auto i = last_block.get_free_space(); i > 0; --i) {
        data_file.write(reinterpret_cast<const char*>(&zero), sizeof(char));
    }

    uint32_t block_number;
    data_file.seekg(12);
    data_file.read(reinterpret_cast<char*>(&block_number), sizeof(uint32_t));
    block_number += 1;
    data_file.seekp(4);
    data_file.write(reinterpret_cast<char*>(&block_number), sizeof(uint32_t));

    data_file.seekp(12);
    data_file.write(reinterpret_cast<char*>(&block_number), sizeof(uint32_t));

    DataBlock new_data_block(last_block.get_ptr(), 0, block_number);
    data_file.seekp(0, std::ios::end);
    auto block_binary = new_data_block.get_binary_representation();
    data_file.write(block_binary.data(), block_binary.size());

    //change last, block's next_ptr
    data_file.seekp(last_block.get_file_offset() + 4);
    uint32_t curr_block_offset = new_data_block.get_ptr();
    data_file.write(reinterpret_cast<const char*>(&curr_block_offset), sizeof(uint32_t));

    return new_data_block;
}

SelectAnswer StorageEngine::select(std::string table_name, std::vector<std::string> columns_names) {
    auto curr_data_block = get_first_block(table_name);
    auto table = tables_.get_table(table_name);

    SelectAnswer answer;
    answer.columns_names = columns_names;
    bool first = true;

    do {
        if (!first) {
            curr_data_block = get_block(table_name, curr_data_block.get_next_ptr());
        }
        first = false;
        TableChunk curr_table_chunk(tables_.get_table(table_name), curr_data_block);
        for(const auto& row : curr_table_chunk.get_rows()) {
            if (row.is_removed()) {
                continue;
            }

            std::vector<std::string> raw_data;

            for (const auto& cell : row.get_cells()) {
                raw_data.emplace_back(cell->get_data());
            }

            std::vector<std::string> formatted_data;
            formatted_data.reserve(raw_data.size());

            for (auto const& col: columns_names) {
                formatted_data.emplace_back(raw_data[table.get_columns_orders().at(col)]);
            }

            answer.rows.emplace_back(formatted_data);
        }
    } while(curr_data_block.get_next_ptr());

    return answer;
}

SelectAnswer StorageEngine::select_all(std::string table_name) {
    auto table = tables_.get_table(table_name);
    std::vector<std::string> all_columns;
    all_columns.reserve(table.get_columns_orders().size());

    for (const auto& it : table.get_ordered_columns()) {
        all_columns.push_back(it.name);
    }
    return select(table_name, all_columns);
}

void StorageEngine::remove(const std::string& table_name, ConditionPtr condition) {
    auto curr_data_block = get_first_block(table_name);
    auto table = tables_.get_table(table_name);

    bool first = true;
    do {
        if (!first) {
            curr_data_block = get_block(table_name, curr_data_block.get_next_ptr());
        }

        first = false;
        TableChunk curr_table_chunk(tables_.get_table(table_name), curr_data_block);

        for(auto& row : curr_table_chunk.get_rows()) {
            if (cond::row_check(table, row, condition)) {
                row.remove();
            }
        }

        rewrite_record(curr_data_block, curr_table_chunk, table);
    } while(curr_data_block.get_next_ptr());
}

void StorageEngine::rewrite_record(const DataBlock& block, TableChunk& table_chunk, const Table& table) {
    std::ofstream data_file;
    // Low level section ahead. Please fasten your seatbelts and don't touch anything.
    data_file.open(table.get_data_file_path().string(), std::ofstream::binary | std::ofstream::out | std::ofstream::in);
    data_file.seekp(block.get_file_offset() + block.get_data_start());

    std::vector<char> out;
    for (auto& row : table_chunk.get_rows()) {
        row.push_binary(out);
    }
    data_file.write(out.data(), out.size());
}

} // namespace st_e
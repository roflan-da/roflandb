#include <table_chunk.h>
#include <storage_engine_exceptions.h>

namespace st_e {
TableChunk::TableChunk(const Table& table, const DataBlock& data_block) {
    std::ifstream data_file;
    data_file.open(table.get_data_file_path().string(), std::ifstream::binary | std::ifstream::in);


    if (!data_file.is_open()) {
        throw TableNotExistException(table.get_name());
    }

    auto data_start_offset = data_block.get_file_offset() + data_block.get_data_start();
    auto data_end_offset = data_block.get_file_offset() + data_block.get_free_offset();
    size_t data_size = data_end_offset - data_start_offset;

    std::vector<char> data;
    data.resize(data_size);
    // read whole block
    data_file.seekg(data_start_offset);
    data_file.read(data.data(), data_size);
    data_file.close();

    size_t curr_data_block_offset = 0;

    while (curr_data_block_offset != data.size()) {
        TableRow::ArrayOfCells cells;
        char internal_flags = data[curr_data_block_offset];
        curr_data_block_offset += sizeof(char);

        // check deletion
        if (internal_flags & 1) {
            continue;
        }

        for (const auto& col : table.get_ordered_columns()) {
            auto read_bytes = col.deserialize(data, cells, curr_data_block_offset);
            curr_data_block_offset += read_bytes;
        }

        rows_.emplace_back(cells, false);
    }
}

} // namespace st_e

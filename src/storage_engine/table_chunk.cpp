#include <table_chunk.h>
#include <storage_engine_exceptions.h>

namespace st_e {
TableChunk::TableChunk(const Table& table, const DataBlock& data_block) {
    std::ifstream data_file;

    data_file.open(table.get_data_file_path().string(), std::ifstream::binary | std::ifstream::in);

    if (!data_file.is_open()) {
        throw TableNotExistException(table.get_name());
    }


    auto current_block_offset = data_block.get_file_offset() + data_block.get_data_start();
    auto data_end_offset = data_block.get_file_offset() + data_block.get_free_offset();

    data_file.seekg(current_block_offset);

    while (current_block_offset != data_end_offset) {
        TableRow::ArrayOfCells cells;

        char internal_flags;
        data_file.read(&internal_flags, sizeof(char));
        current_block_offset += sizeof(char);

        for (const auto& col : table.get_ordered_columns()) {
            auto read_bytes = col.deserialize(data_file, cells);
            current_block_offset += read_bytes;
        }

        rows_.emplace_back(cells, false);
    }
}

} // namespace st_e

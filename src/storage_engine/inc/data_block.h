#pragma once

#include <cstdint>
#include <vector>
#include <configuration.h>

namespace st_e {

/*
 *
 * Data block structure:
 * Data block is contains only metadata
 * Block numeration starts with 1. Block number 0 has special meaning - absence of previous or next block.
 *
 * [uint32_t: previous block number]
 * [uint32_t: next block number]
 * [uint32_t<=DATA_BLOCK_SIZE data start - skip data from previous block]
 * [unit32_t free space offset]
 * [uint32_t current_block_ptr]
 * [DATA_BLOCK_SIZE-HEADER_LENGTH bytes of data]
 *
 * Data File structure:
 * [uint32_t first existing block]
 * [uint32_t last existing block]
 * [uint32_t first deleted block]
 * [uint32_t block counter]
 * [N blocks of data blocks]
 */

class DataBlock {
public:
    static const uint32_t HEADER_LENGTH = 20;

    DataBlock(uint32_t previous_ptr, uint32_t next_ptr, uint32_t data_start, uint32_t free_offset, uint32_t curr_block_ptr);
    DataBlock(uint32_t previous_ptr, uint32_t next_ptr, uint32_t curr_block_ptr);
    uint32_t get_previous_ptr() const { return previous_; }
    uint32_t get_next_ptr() const { return next_; }
    std::vector<char> get_binary_representation() const;

    uint32_t  get_free_space()  const { return DATA_BLOCK_SIZE - free_offset_; }
    size_t get_file_offset() const { return file_offset_; }
    uint32_t  get_free_offset() const { return free_offset_; }
    uint32_t  get_data_start()  const { return data_start_; }
    uint32_t  get_ptr() const { return curr_block_ptr_; }

private:
    uint32_t previous_ = 0;
    uint32_t next_ = 0;
    // skip data from previous block
    uint32_t data_start_ = HEADER_LENGTH;
    // offset to space without records. deleted or existing.
    uint32_t free_offset_ = HEADER_LENGTH;
    uint32_t curr_block_ptr_;
    size_t file_offset_ = DATA_FILE_HEADER_SIZE + (curr_block_ptr_ - 1) * DATA_BLOCK_SIZE;
};

} // namespace st_e

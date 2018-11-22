#pragma once

#include <cstdint>
#include <vector>

namespace st_e {

/*
 *
 * Data block structure:
 * Data block is contains only metadata
 * Block numeration starts with 1. Block number 0 has special meaning - absence of previous or next block.
 *
 * [uint32_t: previous block number]
 * [uint32_t: next block number]
 * [uint32_t<=BLOCK_SIZE data start - skip data from previous block]
 * [unit32_t free space offset]
 * [BLOCK_SIZE-HEADER_LENGTH bytes of data]
 *
 * Data File structure:
 * [uint32_t first existing block]
 * [uint32_t first deleted block]
 * [N blocks of data blocks]
 */

class DataBlock {
public:
    static const uint32_t HEADER_LENGTH = 8;

    DataBlock(uint32_t previous_ptr, uint32_t next_ptr);
    uint32_t get_previous_ptr() const { return previous_; }
    uint32_t get_next_ptr() const { return next_; }
    std::vector<char> get_binary_representation() const;
private:
    uint32_t previous_ = 0;
    uint32_t next_ = 0;
    // skip data from previous block
    uint32_t data_start_ = HEADER_LENGTH;
    // offset to space without records. deleted or existing.
    uint32_t free_offset_ = HEADER_LENGTH;
//    std::vector<char> data_;
};

} // namespace st_e

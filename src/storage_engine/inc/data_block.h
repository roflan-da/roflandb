#pragma once

#include <cstdint>
#include <vector>

namespace st_e {

/*
 *
 * Data block structure:
 * Block numeration starts with 1. Block number 0 has specil meaning - absence of previous or next block.
 *
 * [uint32_t: previous block number]
 * [uint32_t: next block number]
 * [uint32_t<=BLOCK_SIZE data start - skip data from previos block]
 * [unit32_t free space offset]
 * [BLOCK_SIZE-8 bytes of data]
 *
 * Data File structure:
 * [uint32_t first existing block]
 * [uint32_t first deleted block]
 * [N blocks of data blocks]
 */

class DataBlock {
public:
    DataBlock();
    uint32_t get_previous() const { return previous_; }
    uint32_t get_next() const { return next_; }

private:
    uint32_t previous_ = 0;
    uint32_t next_ = 0;
    uint32_t data_start_ = 8;
    uint32_t free_offset_ = 8;
    std::vector<char> data_;
};

} // namespace st_e





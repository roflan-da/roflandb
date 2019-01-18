#include <data_block.h>
#include <cstring>
#include "configuration.h"

namespace st_e {

st_e::DataBlock::DataBlock(uint32_t previous_ptr, uint32_t next_ptr, uint64_t creating_transaction_number, uint32_t data_start, uint32_t free_offset,
        uint32_t curr_block_ptr)
        : previous_(previous_ptr), next_(next_ptr), data_start_(data_start), free_offset_(free_offset),
        curr_block_ptr_(curr_block_ptr), creating_transaction_number_(creating_transaction_number) {}

st_e::DataBlock::DataBlock(uint32_t previous_ptr, uint32_t next_ptr, uint64_t creating_transaction_number, uint64_t expire_transaction_number, uint32_t data_start, uint32_t free_offset,
        uint32_t curr_block_ptr)
        : previous_(previous_ptr), next_(next_ptr), data_start_(data_start), free_offset_(free_offset),
            curr_block_ptr_(curr_block_ptr), creating_transaction_number_(creating_transaction_number), expire_transaction_number_(expire_transaction_number) {}

DataBlock::DataBlock(uint32_t previous_ptr, uint32_t next_ptr, uint64_t creating_transaction_number, uint32_t curr_block_ptr)
    : previous_(previous_ptr), next_(next_ptr), curr_block_ptr_(curr_block_ptr), creating_transaction_number_(creating_transaction_number) {}

std::vector<char> DataBlock::get_binary_representation() const {
    std::vector<char> binary_buffer;
    binary_buffer.resize(HEADER_LENGTH);

    std::memcpy(binary_buffer.data(), &previous_, sizeof(previous_));
    std::memcpy(binary_buffer.data() + sizeof(uint32_t), &next_, sizeof(next_));
    std::memcpy(binary_buffer.data() + 2*sizeof(uint32_t), &data_start_, sizeof(data_start_));
    std::memcpy(binary_buffer.data() + 3*sizeof(uint32_t), &free_offset_, sizeof(free_offset_));
    std::memcpy(binary_buffer.data() + 4*sizeof(uint32_t), &curr_block_ptr_, sizeof(curr_block_ptr_));
    std::memcpy(binary_buffer.data() + 5*sizeof(uint32_t), &creating_transaction_number_, sizeof(creating_transaction_number_));
    std::memcpy(binary_buffer.data() + 5*sizeof(uint32_t) + sizeof(uint64_t), &expire_transaction_number_, sizeof(expire_transaction_number_));
    return binary_buffer;
}

} // namespace st_e

#include <data_block.h>
#include <cstring>
#include "configuration.h"

namespace st_e {

st_e::DataBlock::DataBlock(uint32_t previous_ptr, uint32_t next_ptr, long long file_offset)
    : previous_(previous_ptr), next_(next_ptr), file_offset_(file_offset) {}

std::vector<char> DataBlock::get_binary_representation() const {
    std::vector<char> binary_buffer;
    binary_buffer.resize(HEADER_LENGTH);

    std::memcpy(binary_buffer.data(), &previous_, sizeof(previous_));
    std::memcpy(binary_buffer.data() + sizeof(uint32_t), &next_, sizeof(next_));;
    std::memcpy(binary_buffer.data() + 2*sizeof(uint32_t), &data_start_, sizeof(data_start_));
    std::memcpy(binary_buffer.data() + 3*sizeof(uint32_t), &free_offset_, sizeof(free_offset_));
    return binary_buffer;
}

} // namespace st_e

#include <data_block.h>
#include <cstring>
#include "configuration.h"

namespace st_e {

st_e::DataBlock::DataBlock(uint32_t previous_ptr, uint32_t next_ptr) : previous_(previous_ptr), next_(next_ptr) {
//    data_.reserve(BLOCK_SIZE - HEADER_LENGTH);
}

std::vector<char> DataBlock::get_binary_representation() const {
    std::vector<char> binary_buffer;
    binary_buffer.resize(HEADER_LENGTH);

    std::memcpy(binary_buffer.data(), &previous_, sizeof(previous_));;
}

} // namespace st_e

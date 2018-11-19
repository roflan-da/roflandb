#include "data_block.h"
#include "configuration.h"

namespace st_e {

st_e::DataBlock::DataBlock() {
    data_.reserve(BLOCK_SIZE - 8);
}

} // namespace st_e
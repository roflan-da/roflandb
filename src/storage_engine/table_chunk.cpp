#include "table_chunk.h"

namespace st_e {

    void IntegerTableCell::push_into_buffer(std::vector<char> &buffer) const {
        auto first_free_byte = buffer.size();
        buffer.resize(buffer.size() + sizeof(uint32_t));
        memcpy(buffer.data() + first_free_byte, &data_, sizeof(uint32_t));
    }
} // namespace st_e

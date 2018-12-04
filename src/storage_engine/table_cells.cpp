#include <table_cells.h>

namespace st_e {

void IntegerTableCell::push_into_buffer(std::vector<char>& buffer) const {
    auto first_free_byte = buffer.size();
    buffer.resize(buffer.size() + sizeof(uint32_t));
    memcpy(buffer.data() + first_free_byte, &data_, sizeof(uint32_t));
}

std::string BoolTableCell::get_data() {
    return (data_) ? "true" : "false";
}

void BoolTableCell::push_into_buffer(std::vector<char>& buffer) const {
    auto first_free_byte = buffer.size();
    buffer.resize(buffer.size() + sizeof(bool));
    memcpy(buffer.data() + first_free_byte, &data_, sizeof(bool));
}

void VarCharTableCell::push_into_buffer(std::vector<char> &buffer) const {
    auto first_free_byte = buffer.size();
    buffer.resize(buffer.size() + sizeof(bool));
    memcpy(buffer.data() + first_free_byte, data_.data(), sizeof(bool));
}

} // namespce st_e
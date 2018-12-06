#include <table_cells.h>
#include <cstring>

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

void TableRow::push_binary(std::vector<char>& input) const {
    // first byte is internal value. Value of 0 means that record is not deleted
    input.resize(sizeof(char));
    char internal_flag = 0;
    internal_flag = internal_flag | is_removed_;
    std::memcpy(input.data(), &internal_flag, sizeof(char));

    for (const auto& cell : cells_) {
        cell->push_into_buffer(input);
    }
}

} // namespce st_e
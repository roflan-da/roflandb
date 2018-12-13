#include "inc/table_cells.h"
#include <cstring>
#include <table_cells.h>
#include <boost/algorithm/string.hpp>


namespace st_e {

void IntegerTableCell::push_into_buffer(std::vector<char>& buffer) const {
    auto first_free_byte = buffer.size();
    buffer.resize(buffer.size() + sizeof(uint32_t));
    memcpy(buffer.data() + first_free_byte, &data_, sizeof(uint32_t));
}

void IntegerTableCell::set_value(std::string value) {
    data_ = std::stoi(value);
}

std::string BoolTableCell::get_data() {
    return (data_) ? "true" : "false";
}

void BoolTableCell::push_into_buffer(std::vector<char>& buffer) const {
    auto first_free_byte = buffer.size();
    buffer.resize(buffer.size() + sizeof(bool));
    memcpy(buffer.data() + first_free_byte, &data_, sizeof(bool));
}

void BoolTableCell::set_value(std::string value) {
    value = boost::to_lower_copy(value);
    data_ = value == "true";
}

void VarCharTableCell::push_into_buffer(std::vector<char> &buffer) const {
    auto first_free_byte = buffer.size();
    buffer.resize(buffer.size() + sizeof(bool));
    memcpy(buffer.data() + first_free_byte, data_.data(), sizeof(bool));
}

void VarCharTableCell::set_value(std::string value) {
    data_ = value;
}

void TableRow::push_binary(std::vector<char>& input) const {
    // first byte is internal value. Value of 0 means that record is not deleted
    auto first_free_byte = input.size();
    input.resize(input.size() + sizeof(char));
    char internal_flag = 0;
    internal_flag = internal_flag | is_removed_;
    std::memcpy(input.data()+ first_free_byte, &internal_flag, sizeof(char));

    for (const auto& cell : cells_) {
        cell->push_into_buffer(input);
    }
}

} // namespce st_e
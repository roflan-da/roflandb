#pragma once

#include <string>
#include "data_block.h"

namespace st_e {

class TableCell {
public:
    virtual ~TableCell() = default;
    virtual std::string get_data() = 0;
};

class IntegerTableCell : public TableCell {
public:
    explicit IntegerTableCell(int data) : data_(data) {}
    std::string get_data() override { return std::to_string(data_); }

private:
    int data_;
};

class TableRow {
public:
    explicit TableRow(const std::vector<TableCell>& cells) : cells_(cells) {}

//    std::string get_cell(size_t number){ return cells_[number].get_data(); }
//    std::string to_string();

private:
    std::vector<TableCell> cells_;
};

class TableChunk {
public:
    TableChunk(const DataBlock& data_block);

};

} // namespace st_e

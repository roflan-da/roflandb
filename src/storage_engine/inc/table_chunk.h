#pragma once

#include <utility>
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
    // todo: maybe do like this?
    uint32_t get_value() const { return data_; }

private:
    uint32_t data_;
};

class TableRow {
public:
    explicit TableRow(std::vector<TableCell> cells) : cells_(std::move(cells)) {}

//    std::string get_cell(size_t number){ return cells_[number].get_data(); }
    const std::vector<TableCell>& get_cells() const { return cells_; }

private:
    std::vector<TableCell> cells_;
};

class TableChunk {
public:
    TableChunk(const DataBlock& data_block);

};

} // namespace st_e

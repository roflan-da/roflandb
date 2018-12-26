#pragma once

#include <utility>
#include <string>
#include <data_block.h>
#include <memory>
#include <table.h>
#include <table_cells.h>
#include <fstream>

namespace st_e {


class TableChunk {
public:
    using ArrayOfRows = std::vector<TableRow>;

    TableChunk(const Table& table, const DataBlock& data_block);
    ArrayOfRows& get_rows() { return rows_; }

private:
    ArrayOfRows rows_;

};

} // namespace st_e

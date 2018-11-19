#pragma once

#include <map>
#include <boost/filesystem.hpp>
#include "table.h"

namespace st_e {

class SharedTable {
public:
    SharedTable(const SharedTable&) = delete;
    SharedTable& operator=(SharedTable&) = delete;
    static SharedTable& get_instance();

    const Table& get_table(const std::string& name);
    // rewrites existing table metadata
    void save_table(const Table& table);

private:
    SharedTable() = default;
    std::map<std::string, Table> cached_tables_;

    Table& load_table(const std::string& name);
    void save_to_disk(const Table& table) const;
};

} // namespace st_e

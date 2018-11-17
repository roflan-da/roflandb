#pragma once

#include <map>
#include <boost/filesystem.hpp>
#include "table.h"
namespace st_e {

// singleton NOT thread safe
class SharedTable {
public:
    SharedTable(const SharedTable&) = delete;
    SharedTable& operator=(SharedTable&) = delete;
    static SharedTable& get_instance();

//    std::shared_ptr<Table> get_table(const std::string& name);
    // rewrites existing table metadata
    void save_table(const Table& table);

private:
    SharedTable() = default;
    std::map<std::string, Table> cached_tables_;

    Table& load_table(const std::string& name);
    void save_to_disk(const Table& table);
    boost::filesystem::path get_metadata_file_path(const Table&);
};

} // namespace st_e

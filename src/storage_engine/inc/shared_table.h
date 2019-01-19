#pragma once

#include <map>
#include <memory>
#include <boost/filesystem.hpp>
#include <boost/thread/mutex.hpp>
#include "table.h"
namespace st_e {

class SharedTable {
public:
    SharedTable(const SharedTable&) = delete;
    SharedTable& operator=(SharedTable&) = delete;
    static SharedTable& get_instance();

    const Table& get_table(const std::string& name);
    std::map<std::string, std::shared_ptr<boost::mutex>>& get_locks();
    // rewrites existing table metadata
    void save_table(const Table& table);
    void delete_table(const std::string& table_name);

private:
    SharedTable() = default;
    std::map<std::string, Table> cached_tables_;
    std::map<std::string, std::shared_ptr<boost::mutex>> table_locks;

    Table& load_table(const std::string& name);
    void save_to_disk(const Table& table) const;
};

} // namespace st_e

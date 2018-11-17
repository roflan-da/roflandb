#pragma once

#include <map>
#include "table.h"
namespace st_e {

// singleton NOT thread safe
class SharedTable {
public:
    SharedTable(const SharedTable&) = delete;
    SharedTable& operator=(SharedTable&) = delete;
    static SharedTable& get_instance();

    std::shared_ptr<Table> get_table(const std::string& name);

private:
    SharedTable() = default;
    std::map<std::string, std::shared_ptr<Table>> cached_tables_;

    std::shared_ptr<Table> load_table(const std::string& name);

};

} // namespace st_e

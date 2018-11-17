#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <map>
#include <string>
#include "shared_table.h"

namespace st_e {

class StorageEngine {
public:
    StorageEngine() = default;

    void add_table(const Table& table);
//    bool delete_table(std::string table_name);

//    TablePtr get_table_by_name(std::string table_name) override;

//    void insert(const std::string& table_name, std::vector<std::pair<std::string, std::string>> row);

//    SelectAnswer select(std::string table_name, std::vector<std::string> columns_names) override;
//    SelectAnswer select_all(std::string table_name) override;
//

private:
    SharedTable& tables_ = SharedTable::get_instance();
};

}//namespace st_e

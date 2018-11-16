#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <map>
#include <string>
#include "table.h"

namespace st_e {

class StorageEngine {
public:
    using TablePtr = std::shared_ptr<Table>;

    StorageEngine();

    void add_table(TablePtr table);
//    bool delete_table(std::string table_name);

//    TablePtr get_table_by_name(std::string table_name) override;

//    void insert(std::string table_name, std::vector<std::pair<std::string, std::string>> row);

//    SelectAnswer select(std::string table_name, std::vector<std::string> columns_names) override;
//    SelectAnswer select_all(std::string table_name) override;
//
//    void save();
//    void load();

private:
    std::map<std::string, TablePtr> tables_;
};

}//namespace st_e

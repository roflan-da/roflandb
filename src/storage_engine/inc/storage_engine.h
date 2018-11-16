#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <map>
#include <string>
#include "i_storage_engine.h"
#include "table.h"

namespace st_e {

class StorageEngine : public IEngineStorage {
public:
    using TablePtr = std::shared_ptr<Table>;

    StorageEngine();

    void add_table(TablePtr table) override;
    bool delete_table(std::string table_name) override;

    TablePtr get_table_by_name(std::string table_name) override;

    void insert(std::string table_name, std::vector<std::pair<std::string, std::string>> row) override;

//    SelectAnswer select(std::string table_name, std::vector<std::string> columns_names) override;
//    SelectAnswer select_all(std::string table_name) override;

    void save() override;
    void load() override;

private:
    std::map<std::string, TablePtr> tables_;
};

}//namespace st_e

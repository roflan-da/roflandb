#pragma once

#include "i_storage_engine.h"
#include "table.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <map>
#include <string>

namespace st_e {

    class StorageEngine : public IEngineStorage {
    public:
        void add_table(std::shared_ptr<Table> table) override;
        void delete_table(std::string table_name) override;
        std::shared_ptr<Table> get_table_by_name(std::string table_name) override;
        void insert(std::string table_name, std::vector<std::pair<std::string, std::string>> raw) override;
        void save() override;
        void load() override;

    private:
        std::map<std::string, std::shared_ptr<Table>> tables_;
    };

}//namespace st_e

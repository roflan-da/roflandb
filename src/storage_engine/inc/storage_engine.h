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
        void addTable(std::shared_ptr<Table> table) override;
        void deleteTable(std::string table_name) override;
        std::shared_ptr<Table> getTableByName(std::string table_name) override;
        void Save() override;
        void Load() override;

    private:
        std::map<std::string, std::shared_ptr<Table>> tables_;
    };

}//namespace st_e

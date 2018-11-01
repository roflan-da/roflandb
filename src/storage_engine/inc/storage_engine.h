#pragma once

#include "i_storage_engine.h"
#include "table.h"
#include <memory>
#include <map>
#include <string>

namespace st_e {

    class StorageEngine : public IEngineStorage {
    public:
        void addTable(std::shared_ptr<Table> table);
        void deleteTable(std::string table_name);
        std::map<std::string, std::shared_ptr<Table>>::iterator findTable(std::string table_name);
        std::string Save();
        void Load(std::string tables_string);

    private:
        std::map<std::string, std::shared_ptr<Table>> tables_;
    };

}//namespace st_e

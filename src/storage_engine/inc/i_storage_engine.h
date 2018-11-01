#pragma once

#include "table.h"

namespace st_e {

class IEngineStorage {
public:
    virtual std::shared_ptr<Table> getTableByName(std::string) = 0;
    virtual void addTable(std::shared_ptr<Table> table) = 0;
    virtual void deleteTable(std::string table_name) = 0;
    virtual void Save() = 0;
    virtual void Load() = 0;
};

}//namespace st_e

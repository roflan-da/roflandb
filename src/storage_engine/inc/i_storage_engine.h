#pragma once

#include <mem.h>
#include "table.h"

namespace st_e {

class IEngineStorage {
public:
    virtual std::shared_ptr<Table> getTableByName(std::string) = 0;
};

}//namespace st_e

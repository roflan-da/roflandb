#pragma once

#include <table.h>

namespace st_e {

class IEngineStorage {
public:
    virtual std::shared_ptr<Table> get_table_by_name(std::string) = 0;
    virtual void add_table(std::shared_ptr<Table> table) = 0;
    virtual void delete_table(std::string table_name) = 0;
    virtual void save() = 0;
    virtual void load() = 0;
};

}//namespace st_e

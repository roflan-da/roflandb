#pragma once

#include <table.h>

namespace st_e {

class IEngineStorage {
public:
    virtual std::shared_ptr<Table> get_table_by_name(std::string) = 0;
    virtual void add_table(std::shared_ptr<Table> table) = 0;
    virtual bool delete_table(std::string table_name) = 0;
    virtual void insert(std::string table_name, std::vector<std::pair<std::string, std::string>> raw) = 0;
    virtual SelectAnswer select(std::string table_name, std::vector<std::string> columns_names) = 0;
    virtual void save() = 0;
    virtual void load() = 0;
};

}//namespace st_e

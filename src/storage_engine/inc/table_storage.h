#pragma once

#include "table.h"
#include <memory>
#include <map>
#include <string>

class TableStorage{
public:
    void addTable(std::shared_ptr<Table> table);
    void deleteTable(std::string table_name);
    std::map<std::string, std::shared_ptr<Table>>::iterator findTable(std::string table_name);
    std::string Save();
    void Load(std::string tables_string);
private:
    std::map<std::string, std::shared_ptr<Table>> tables_;
};

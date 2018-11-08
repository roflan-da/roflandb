#pragma once
#include "i_storage_engine.h"

class StorageEngineMock : public st_e::IEngineStorage {
public:
    void addTable(std::shared_ptr<st_e::Table> table) override;
    void deleteTable(std::string table_name) override;
    std::shared_ptr<st_e::Table> getTableByName(std::string table_name) override;
    void Save() override;
    void Load() override;

};


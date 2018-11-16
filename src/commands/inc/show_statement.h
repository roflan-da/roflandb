#pragma once

#include "string"
#include <vector>
#include <memory>
#include <SQL_Statement.h>


namespace cmd{
enum ShowType{
    TABLE
};

class ShowStatement : public SQLStatement{
public:
    ShowStatement();

    explicit ShowStatement(ShowType type);
    explicit ShowStatement(ShowType type, std::string name);

    void execute(st_e::IEngineStorage& storage_engine) override;

    ShowType get_type();
    std::string get_name();
private:
    ShowType type_;
    std::string name_;
};
} //namespace cmd

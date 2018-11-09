#pragma once

#include "string"
#include <vector>
#include <SQL_Statement.h>

namespace cmd{

    enum DropType{
        DROP_TABLE,
        DROP_DATABASE
    };

    class DropStatement : public SQLStatement{
    public:
        DropStatement();

        void execute(st_e::IEngineStorage& storage_engine) override;

        explicit DropStatement(std::string table_name);
        explicit DropStatement(DropType type, std::string name);

        DropType get_type() const;
        std::string get_name() const;

    private:
        DropType type_;
        std::string name_;
    };
} //namespace cmd

#pragma once

#include "string"
#include <vector>
#include <memory>
#include <sql_statement.h>


namespace cmd{

    enum ShowType{
        TABLE
    };

    class ShowStatement : public SqlStatement{
    public:
        ShowStatement();

        explicit ShowStatement(ShowType type);
        explicit ShowStatement(ShowType type, std::string name);

        void execute(st_e::StorageEngine& storage_engine) override;

        ShowType get_type();
        std::string get_name();
    private:
        ShowType type_;
        std::string name_;
    };
} //namespace cmd

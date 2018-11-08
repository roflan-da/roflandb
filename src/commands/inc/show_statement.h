#pragma once

#include "string"
#include <vector>
#include <memory>
#include <SQL_Statement.h>


namespace cmd{

    enum ShowType{
//        COLUMN,
        TABLE
//        DATABASE
    };

    class ShowStatement : public SQLStatement{
    public:
        ShowStatement();

        explicit ShowStatement(ShowType type);

        void execute(std::shared_ptr<st_e::IEngineStorage> engine_storage) override;

        ShowType get_type();
        std::string get_name();
    private:
        ShowType type_;
        std::string name_;
    };
} //namespace cmd

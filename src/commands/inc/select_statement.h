#pragma once

#include "string"
#include <vector>
#include <memory>
#include <SQL_Statement.h>
//#include "queryc"

namespace cmd {

    enum SelectType{
        ALL,
        VARIABLE
    };

    class SelectStatement : public SQLStatement {
    public:
        SelectStatement();

        void execute(std::shared_ptr<st_e::IEngineStorage> engine_storage) override;

        explicit SelectStatement(std::string table_name, SelectType type = ALL);

        void set_col_names(std::shared_ptr<std::vector<std::string>> cols_names);
    private:
        std::string table_name_;
        SelectType type_;
        std::vector<std::string> cols_names_;
    };

} //namespace cmd
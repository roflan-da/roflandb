#pragma once

#include "string"
#include <vector>
#include <memory>
#include <SQL_Statement.h>

namespace cmd{
    class InsertStatement : public SQLStatement {
    public:
        InsertStatement();

        explicit InsertStatement(std::string table_name);

        std::string get_table_name();

        void set_columns_vals(std::shared_ptr<std::vector<std::string>> columns_vals);
        void set_columns_names(std::shared_ptr<std::vector<std::string>> columns_names);

        void execute(st_e::IEngineStorage &engine_storage) override;

        std::vector<std::pair<std::string, std::string>> get_name_val();
    private:
        std::string table_name_;
        std::vector<std::string> columns_names_;
        std::vector<std::string> columns_vals_;
    };
} //namespace cmd

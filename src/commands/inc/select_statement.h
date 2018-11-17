#pragma once

#include "string"
#include <vector>
#include <memory>
#include <sql_statement.h>
#include "condition.h"

namespace cmd {

    enum SelectType{
        ALL,
        VARIABLE
    };

    class SelectStatement : public SqlStatement {
    public:
        SelectStatement();

        void execute(st_e::StorageEngine& storage_engine) override;

        explicit SelectStatement(std::string table_name);

        explicit SelectStatement(std::string table_name,
                std::shared_ptr<std::vector<std::string>> cols_names,
                SelectType type = ALL);
    private:
        std::string table_name_;
        SelectType type_;
        std::vector<std::string> cols_names_;
    };

} //namespace cmd
#pragma once

#include "string"
#include <vector>
#include <memory>
#include <sql_statement.h>

namespace cmd{
    class InsertStatement : public SqlStatement {
    public:
        InsertStatement();
        ~InsertStatement() override = default;
        explicit InsertStatement(std::string table_name,
                                 std::shared_ptr<std::vector<std::string>> cols_names,
                                 std::shared_ptr<std::vector<std::string>> cols_values);

        void execute(st_e::StorageEngine &engine_storage) override;
    private:
        bool is_valid(st_e::StorageEngine& engine_storage) override;

        friend void SqlStatement::set_message(std::string message);

        std::vector<std::pair<std::string, std::string>> get_name_val();
        std::string table_name_;
        std::vector<std::string> columns_names_;
        std::vector<std::string> columns_vals_;
    };
} //namespace cmd

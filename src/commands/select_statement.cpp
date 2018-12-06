#include <iostream>
#include <sstream>
#include "select_statement.h"
#include "storage_engine_exceptions.h"

cmd::SelectStatement::SelectStatement() : SqlStatement(SELECT) {}

cmd::SelectStatement::SelectStatement(std::string table_name,
                                      std::shared_ptr<std::vector<std::string>> cols_names,
                                      ListType type) :
        SqlStatement(SELECT),
        table_name_(std::move(table_name)),
        type_(type),
        cols_names_(*cols_names.get()) {}

void cmd::SelectStatement::execute() {
    st_e::SelectAnswer t = type_ == ALL ? st_e::StorageEngine::get_instance().select_all(table_name_) :
                           st_e::StorageEngine::get_instance().select(table_name_, cols_names_);
    std::string message;
    std::stringstream message_stream;

    //todo: fix sigsegv error
//    std::vector<long long int> maxwidth(t.rows[0].size(), 0);
//    for (auto& row : t.rows) {
//        for (auto cell = 0; cell < row.size(); ++cell) {
//            if (row[cell].size() >= maxwidth[cell]) {
//                maxwidth[cell] = row[cell].size() + 1; //1 for spacing
//            }
//        }
//    }
//    message_stream << "|";
//    for (int i = 0; i < t.columns_names.size(); ++i) {
//        message_stream << std::setw(maxwidth[i]) << t.columns_names[i] + "|";
//    }
//    message_stream << std::endl;
//    for (auto& row : t.rows) {
//        message_stream << "|";
//        for (auto cell = 0; cell < row.size(); ++cell) {
//            message_stream << std::setw(maxwidth[cell]) << row[cell] + "|";
//        }
//        message_stream << std::endl;
//    }
//    message_stream << std::endl;
//    message = message_stream.str();
    for (auto& row : t.rows) {
        for (const auto& j : row) {
            message += j + " ";
        }
        message += '\n';
    }
    set_message(message);
}

cmd::SelectStatement::SelectStatement(const std::string& table_name) : table_name_(table_name), type_(ALL){}

bool cmd::SelectStatement::is_valid() const {
    return false;
}

void cmd::SelectStatement::add_conditions(std::shared_ptr<cond::QueryConditions> conditions) {
    conditions_ = *conditions.get();
}

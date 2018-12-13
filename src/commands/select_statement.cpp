#include <utility>

#include <iostream>
#include <sstream>
#include <iomanip>
#include <select_statement.h>

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
    if (!is_valid()){
        //TODO: Exception or message
        return;
    }
    st_e::SelectAnswer t = type_ == ALL ? st_e::StorageEngine::get_instance().select_all(table_name_, conditions_) :
                           st_e::StorageEngine::get_instance().select(table_name_, cols_names_, conditions_);
    std::string message;
    std::stringstream message_stream;

    //todo: fix sigsegv error
    std::vector<long long unsigned int> maxwidth(t.columns_names.size(), 0);
    for (size_t column = 0; column < t.columns_names.size(); ++column){
        if (t.columns_names[column].size() >= maxwidth[column]){
            maxwidth[column] = t.columns_names[column].size() + 1;//1 for spacing
        }
    }
    for (auto& row : t.rows) {
        for (size_t column = 0; column < row.size(); ++column) {
            if (row[column].size() >= maxwidth[column]) {
                maxwidth[column] = row[column].size() + 1; //1 for spacing
            }
        }
    }
    message_stream << "|";
    for (size_t  i = 0; i < t.columns_names.size(); ++i) {
        message_stream << std::setw(maxwidth[i]) << t.columns_names[i] + "|";
    }
    message_stream << std::endl;
    for (auto& row : t.rows) {
        message_stream << "|";
        for (size_t  cell = 0; cell < row.size(); ++cell) {
            message_stream << std::setw(maxwidth[cell]) << row[cell] + "|";
        }
        message_stream << std::endl;
    }
    message = message_stream.str();
    set_message(message);
}

cmd::SelectStatement::SelectStatement(const std::string& table_name) : table_name_(table_name), type_(ALL){}

bool cmd::SelectStatement::is_valid() {
    try {
        auto table = st_e::StorageEngine::get_instance().get_table_by_name(table_name_);
        auto table_cols = table.get_columns_orders();

        if(type_ == ALL){
            for(const auto &item : table_cols) {
                cols_names_.push_back(item.first);
            }
        }
        else {
            if (cols_names_.size() != table_cols.size()) {
                return false;
            }
            for (size_t i = 0; i < cols_names_.size(); ++i) {
                for (size_t j = i + 1; j < cols_names_.size(); ++j) {
                    if (cols_names_[i] == cols_names_[j]) {
                        return false;
                    }
                }
            }
            for (const auto &cols_name : cols_names_) {
                auto found = table_cols.find(cols_name);
                if (found == table_cols.end()) {
                    return false;
                }
            }
        }
    if (!is_condition_valid(conditions_, table_cols, table.get_ordered_columns())){
        return false;
    }
    }
    catch (st_e::TableNotExistException &e) {
        return false;
    }
    return true;
}

bool cmd::SelectStatement::is_condition_valid(const std::shared_ptr<cond::Condition>& condition,
                        st_e::Table::MapOfColumns& columns_names, const st_e::Table::ArrayOfColumns& columns_types) {
    if (condition->type() == cond::ALWAYS_TRUE)
        return true;
    if ((condition->type() == cond::OR) || ((condition->type() == cond::AND))){
        bool a = is_condition_valid(dynamic_cast<cond::ComplexCondition*>(condition.get())->left(), columns_names, columns_types);
        bool b = is_condition_valid(dynamic_cast<cond::ComplexCondition*>(condition.get())->right(), columns_names, columns_types);
        return a & b;
    }
    else{
        std::string s;
        s = dynamic_cast<cond::SimpleCondition*>(condition.get())->column_name();
        st_e::Column column = columns_types[columns_names.at(s)];
        try {
            switch (column.type) {
                case st_e::Column::INT :
                    std::stoi(dynamic_cast<cond::SimpleCondition *>(condition.get())->value());
                    break;
                case st_e::Column::CHAR:

                    break;
                case st_e::Column::VARCHAR:

                    break;
                case st_e::Column::TEXT:

                    break;
                case st_e::Column::BOOL:

                    break;
            }
        }
        catch (std::invalid_argument& e){
            return false;
        }
    }
    return true;
}

void cmd::SelectStatement::add_conditions(std::shared_ptr<cond::Condition> conditions) {
    conditions_ = std::move(conditions);
}

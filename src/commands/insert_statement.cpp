#include <utility>
#include <sstream>
#include "insert_statement.h"
#include "storage_engine_exceptions.h"

cmd::InsertStatement::InsertStatement(std::string table_name,
                                      std::shared_ptr<std::vector<std::string>> cols_names,
                                      std::shared_ptr<std::vector<std::string>> cols_values) :
        SqlStatement(INSERT),
        list_type_(VARIABLE),
        table_name_(std::move(table_name)),
        columns_names_(*cols_names.get()),
        columns_vals_(*cols_values.get()){}

cmd::InsertStatement::InsertStatement(std::string table_name,
                                      std::shared_ptr<std::vector<std::string>> cols_values) :
        SqlStatement(INSERT),
        list_type_(ALL),
        table_name_(std::move(table_name)),
        columns_vals_(*cols_values.get()){}

cmd::InsertStatement::InsertStatement() : SqlStatement(INSERT) {}

st_e::TableRow cmd::InsertStatement::get_row() const {
    auto table = st_e::StorageEngine::get_instance().get_table_by_name(table_name_);
    std::vector<std::shared_ptr<st_e::TableCell>> cells;
    // todo: add better check
    cells.resize(table.get_ordered_columns().size());

    for (size_t i = 0; i < columns_names_.size(); ++i) {
        auto found_col_index = table.get_columns_orders()[columns_names_[i]];
        auto found_col = table.get_column(columns_names_[i]);

        switch (found_col.type)
            {
            case (st_e::Column::INT) : {
                cells[found_col_index] = std::make_shared<st_e::IntegerTableCell>(std::stoi(columns_vals_[i]));
                break;
            }
            case (st_e::Column::VARCHAR) : {
                break;
            }
            case (st_e::Column::TEXT) : {
                break;
            }
            case (st_e::Column::CHAR) : {
                break;
            }
            case st_e::Column::BOOL:{
                break;
            }
            }
    }
    return st_e::TableRow(cells, false);
    /*std::vector<std::pair<std::string, std::string>> result;
    if (columns_names_.size() != columns_vals_.size()){
        return result;
    }
    for (size_t i = 0; i < columns_vals_.size(); ++i) {
        result.emplace_back(std::make_pair(columns_names_[i], columns_vals_[i]));
    }
    return result; */
}

void cmd::InsertStatement::execute() {
    if (is_valid()){
        st_e::StorageEngine::get_instance().insert(table_name_, get_row());

    } else {
        //TODO: Exception or message
        throw st_e::StorageEngineException("ERROR");
    }
//    set_message("INSERT INTO " + table_name_ + " SUCCESSFUL.");
    //    engine_storage.save();
}

bool cmd::InsertStatement::is_valid() {
    try {
        auto table = st_e::StorageEngine::get_instance().get_table_by_name(table_name_);
        auto table_cols = table.get_columns_orders();
        if(list_type_ == ALL){
            for(const auto &item : table_cols) {
                columns_names_.push_back(item.first);
            }
        }
        else {
            if ((columns_names_.size() != table_cols.size()) || (columns_vals_.size() != table_cols.size())) {
                return false;
            }
            for (size_t i = 0; i < columns_names_.size(); ++i) {
                for (size_t j = i + 1; j < columns_names_.size(); ++j) {
                    if (columns_names_[i] == columns_names_[j]) {
                        return false;
                    }
                }
            }
            bool sort_needed = false;
            for (size_t i = 0; i < columns_names_.size(); ++i) {
                auto found = table_cols.find(columns_names_[i]);
                if (found == table_cols.end()) {
                    return false;
                }
                else if (i != found->second){
                    sort_needed = true;
                }
            }
            if (sort_needed){
                std::vector<std::string> new_columns_names(columns_names_.size());
                std::vector<std::string> new_columns_values(columns_vals_.size());
                for (size_t i = 0; i < columns_names_.size(); ++i) {
                    auto found = table_cols.find(columns_names_[i]);
                    new_columns_names[found->second] = columns_names_[i];
                    new_columns_values[found->second] = columns_vals_[i];
                }
                columns_names_ = new_columns_names;
                columns_vals_ = new_columns_values;
            }
        }
        for (size_t i = 0; i < columns_names_.size(); ++i) {
            auto found_col = table.get_column(columns_names_[i]);
            switch (found_col.type)
            {
            case (st_e::Column::INT) : {
                if (columns_vals_[i].empty()) {
                    return false;
                }
                std::stringstream ss;
                ss << columns_vals_[i];
                int integer;
                std::string string;
                ss >> integer;
                ss >> string;
                if (!string.empty() || (integer == 0 && columns_vals_[i] != "0")) { //HOLY SHIT (still better than static_cast)
                    return false; //TEST!!!
                }
                break;
            }
            case (st_e::Column::VARCHAR) : {
                //TODO: ограничение по длине строки
                break;
            }
            case (st_e::Column::TEXT) : {
                break;
            }
            case (st_e::Column::CHAR) : {
                //is it correct?
                if (columns_vals_[i].size() > 1) {
                    return false;
                }
                break;
            }
            default: {
                return false;
            }
            }
        }
    }
    catch (st_e::TableNotExistException& e){
        return false;
    }
    return true;
}

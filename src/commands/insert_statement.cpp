#include <utility>
#include <sstream>
#include "insert_statement.h"
#include "storage_engine_exceptions.h"



cmd::InsertStatement::InsertStatement(std::string table_name,
                                      std::shared_ptr<std::vector<std::string>> cols_names,
                                      std::shared_ptr<std::vector<std::string>> cols_values) :
        SqlStatement(INSERT),
        table_name_(std::move(table_name)),
        columns_names_(*cols_names.get()),
        columns_vals_(*cols_values.get()){}

cmd::InsertStatement::InsertStatement() : SqlStatement(INSERT) {}

st_e::TableRow cmd::InsertStatement::get_row() const {
    auto table_cols = st_e::StorageEngine::get_instance().get_table_by_name(table_name_).get_columns();
    std::vector<std::shared_ptr<st_e::TableCell>> rows;
    for (auto col_name : columns_names_) {
        auto found_col = table_cols.find(col_name)->second;
        switch (found_col.type)
        {
        case (st_e::Column::INT) : {
            rows.emplace_back(new st_e::IntegerTableCell(std::stoi(col_value)));
            break;
        }
        case (st_e::Column::STRING) : {
            break;
        }
        case (st_e::Column::TEXT) : {
            break;
        }
        case (st_e::Column::CHAR) : {
            break;
        }
        }
    }
    return st_e::TableRow(rows);
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
    }
//    set_message("INSERT INTO " + table_name_ + " SUCCESSFUL.");
    //    engine_storage.save();
}

bool cmd::InsertStatement::is_valid() const {
    if (columns_names_.size() != columns_vals_.size()){
        return false;
    }
    try {
        auto table = st_e::StorageEngine::get_instance().get_table_by_name(table_name_);
        auto table_cols = table.get_columns();
        for (const auto &col_name : columns_names_) {
            auto found = table_cols.find(col_name);
            if (found == table_cols.end()) {
                return false;
            }
        }
        for (size_t i = 0; i < columns_names_.size(); ++i) {
            auto found_col = table_cols.find(columns_names_[i])->second;
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
            case (st_e::Column::STRING) : {
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

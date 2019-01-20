#include "update_statement.h"
#include "storage_engine_exceptions.h"

cmd::UpdateStatement::UpdateStatement(std::string table_name,
                                      std::shared_ptr<std::vector<std::pair<std::string, std::string>>> updated_vals,
                                      std::shared_ptr<cond::Condition> conditions) :
                                      table_name_(table_name),
                                      updated_vals_(updated_vals),
                                      conditions_(conditions){}

void cmd::UpdateStatement::execute() {
    check_valid();
    st_e::StorageEngine::get_instance().update(table_name_, updated_vals_, conditions_);
}

void cmd::UpdateStatement::check_valid() {
    try {
        auto table = st_e::StorageEngine::get_instance().get_table_by_name(table_name_);
        auto table_cols = table.get_columns_orders();
        for (size_t i = 0; i < (*updated_vals_).size(); ++i) {
            for (size_t j = i + 1; j < (*updated_vals_).size(); ++j) {
                if ((*updated_vals_)[i].first == (*updated_vals_)[j].first) {
                    throw st_e::InsertDuplicateColumnsException((*updated_vals_)[j].first);
                }
            }
        }
        for (size_t i = 0; i < (*updated_vals_).size(); ++i) {
            auto found = table_cols.find((*updated_vals_)[i].first);
            if (found == table_cols.end()) {
                throw st_e::InsertIncorrectColumnNameException((*updated_vals_)[i].first);
            }
        }
        for (size_t i = 0; i < (*updated_vals_).size(); ++i) {
            auto found_col = table.get_column((*updated_vals_)[i].first);
            switch (found_col.type)
            {
                case (st_e::Column::INT) : {
                    if ((*updated_vals_)[i].second.empty()) {
                        throw st_e::InsertValidException();
                    }
                    std::stringstream ss;
                    ss << (*updated_vals_)[i].second;
                    int integer;
                    std::string string;
                    ss >> integer;
                    ss >> string;
                    if (!string.empty() || (integer == 0 && (*updated_vals_)[i].second != "0")) { //HOLY SHIT (still better than static_cast)
                        throw st_e::InsertValidException(); //TEST!!!
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
                    if ((*updated_vals_)[i].first.size() > 1) {
                        throw st_e::InsertValidException();
                    }
                    break;
                }
                default: {
                    throw st_e::InsertValidException();
                }
            }
        }
        if (!is_condition_valid(conditions_, table_cols, table.get_ordered_columns())){
            throw st_e::SelectConditionsNotValidException();
        }
    }
    catch (st_e::TableNotExistException& e){
        throw st_e::InsertValidException();
    }
}

bool cmd::UpdateStatement::is_condition_valid(const std::shared_ptr<cond::Condition>& condition,
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

#include "delete_statement.h"
#include "storage_engine_exceptions.h"

cmd::DeleteStatement::DeleteStatement(std::string table_name, std::shared_ptr<cond::Condition> conditions) :
    table_name_(table_name), conditions_(conditions){}

void cmd::DeleteStatement::check_valid() {
    //if (!is_condition_valid(conditions_, table_cols, table.get_ordered_columns())){
      //  throw st_e::SelectConditionsNotValidException();
    //}
}

bool cmd::DeleteStatement::is_condition_valid(const std::shared_ptr<cond::Condition>& condition,
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

void cmd::DeleteStatement::execute() {
    st_e::StorageEngine::get_instance().remove(table_name_, conditions_);
}

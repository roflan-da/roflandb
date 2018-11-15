#include <utility>

#include <insert_statement.h>


cmd::InsertStatement::InsertStatement(std::string table_name,
                                      std::shared_ptr<std::vector<std::string>> cols_names,
                                      std::shared_ptr<std::vector<std::string>> cols_values) :
        SQLStatement(INSERT),
        table_name_(std::move(table_name)),
        columns_names_(*cols_names.get()),
        columns_vals_(*cols_values.get()){}

cmd::InsertStatement::InsertStatement() : SQLStatement(INSERT) {}

std::vector<std::pair<std::string, std::string>> cmd::InsertStatement::get_name_val() {
    std::vector<std::pair<std::string, std::string>> result;
    if (columns_names_.size() != columns_vals_.size()){
        return result;
    }
    for (size_t i = 0; i < columns_vals_.size(); ++i) {
        result.emplace_back(std::make_pair(columns_names_[i], columns_vals_[i]));
    }
    return result;
}

void cmd::InsertStatement::execute(st_e::IEngineStorage& engine_storage) {
    engine_storage.insert(table_name_, this->get_name_val());
    set_message("INSERT INTO " + table_name_ + " SUCCESSFUL.");
    //    engine_storage.save();
}

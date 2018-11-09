#include <utility>

#include <insert_statement.h>


cmd::InsertStatement::InsertStatement() = default;

cmd::InsertStatement::InsertStatement(std::string table_name) : table_name_(std::move(table_name)){

}

std::string cmd::InsertStatement::get_table_name() {
    return table_name_;
}

void cmd::InsertStatement::set_columns_vals(std::shared_ptr<std::vector<std::string>> columns_vals) {
    columns_vals_ = *columns_vals.get();
}

void cmd::InsertStatement::set_columns_names(std::shared_ptr<std::vector<std::string>> columns_names) {
    columns_names_ = *columns_names.get();
}

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
    std::vector<std::pair<std::string, std::string>> raw;
    for (size_t i = 0; i < columns_names_.size(); i++) {
        raw.emplace_back(columns_names_[i], columns_vals_[i]);
    }
    engine_storage.insert(table_name_, raw);
//    engine_storage.save();
}

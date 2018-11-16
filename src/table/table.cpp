#include <table.h>
#include "inc/table.h"

namespace st_e {

std::string TableRow::to_string() {
    std::string ans;
    for (const auto& cell : cells_) {
        ans += cell->get_data() + " ";
    }
    return ans;
}

Table::Table(TableBuilder builder) {
    name_ = builder.get_table_name();
    columns_ = builder.get_columns();
}

std::string Table::get_sql() {
    std::string answer;
    answer = "CREATE TABLE \'" + name_ + "\' (";
    for (size_t i = 0; i < columns_.size(); i++){
        if (i > 0) {
            answer += ", ";
        }
        answer += "\'" + columns_[i]->name + "\' " + enum_to_string(columns_[i]->type);
    }
    answer += ");";
    return answer;
}

std::string Table::to_string() {
    std::string table_string;
    table_string = name_ + " " + std::to_string(columns_.size()) + " ";
    for (auto& column : columns_) {
        table_string += std::to_string(column->type) + " " + column->name + " ";
    }
    table_string += std::to_string(rows_.size()) + " ";
    for (auto& row : rows_) {
        table_string += row->to_string();
    }
    return table_string;
}

std::string Table::enum_to_string(ColumnType columnType){   //мб заменить на map
    switch (columnType){
        case INT:
            return "INT";
        case STRING:
            return "STRING";
        case CHAR:
            return "CHAR";
        case TEXT:
            return "TEXT";
        default:
            return "";
    }
}

    void Table::insert(std::vector<std::pair<std::string, std::string>> row) {
        std::vector<std::shared_ptr<TableCell>> cells;
        cells.reserve(row.size());
        for (const auto& i : row) {
            cells.push_back(create_cell(i));
        }
        std::shared_ptr<TableRow> table_row(new TableRow(cells));
        rows_.push_back(table_row);
    }

    void Table::insert(std::vector<std::pair<ColumnType , std::string>> row) {
        std::vector<std::shared_ptr<TableCell>> cells;
        cells.reserve(row.size());
        for (const auto& i : row) {
            cells.push_back(create_cell(i));
        }
        std::shared_ptr<TableRow> table_row(new TableRow(cells));
        rows_.push_back(table_row);
    }

    std::shared_ptr<TableCell> Table::create_cell(std::pair<std::string, std::string> cell) {
        ColumnType type;
        for (auto& column : columns_) {
            if (column->name == cell.first){        //добавить проверку на существование
                type = column->type;
            }
        }
        return create_cell({type, cell.second});
    }

    std::shared_ptr<TableCell> Table::create_cell(std::pair<ColumnType, std::string> cell) {
        switch (cell.first){
            case (INT):
                std::shared_ptr<IntegerTableCell> c(new IntegerTableCell(std::stoi(cell.second)));
                std::shared_ptr<TableCell> cc = c;
                return cc;
        }
    }

    SelectAnswer Table::select(std::vector<std::string> columns_names) {
        SelectAnswer selectAnswer;
        std::vector<size_t> needed_columns;
        for (size_t i = 0; i < columns_.size(); i++){
            for (const auto& columns_name : columns_names) {
                if (columns_name == columns_[i]->name){
                    needed_columns.push_back(i);
                    break;
                }
            }
        }
        for (size_t i = 0; i < rows_.size(); i++){
            selectAnswer.rows.emplace_back();
            for (const auto& needed_column : needed_columns) {
                selectAnswer.rows[i].push_back(rows_[i]->get_cell(needed_column));
            }
        }
        selectAnswer.columns_names = std::move(columns_names);
        return selectAnswer;
    }

    SelectAnswer Table::select_all() {
        SelectAnswer selectAnswer;
        selectAnswer.rows.resize(rows_.size());
        for (size_t i = 0; i < rows_.size(); i++){
            for (size_t j = 0; j < columns_.size(); j++){
                selectAnswer.rows[i].push_back(rows_[i]->get_cell(j));
            }
        }
        selectAnswer.columns_names.reserve(columns_.size());
        for (auto& column : columns_) {
            selectAnswer.columns_names.push_back(column->name);
        }
        return selectAnswer;
    }

    ColumnType Table::get_column_type(std::string column_name) {
        for (auto& column : columns_) {
            if (column->name == column_name){
                return column->type;
            }
        }
        return NONE;
    }


    Column::Column(ColumnType type, std::string name) :
        type(type),
        name(std::move(name)) {}
}//namespace st_e
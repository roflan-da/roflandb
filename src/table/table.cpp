#include <utility>
#include <table.h>


#include "inc/table.h"

namespace st_e {

//Table
Table::Table(TableBuilder builder) {
    name_ = builder.get_table_name();
    columns_ = builder.get_columns();

}

std::string Table::get_sql() {
    std::string answer;
    answer = "CREATE TABLE \'" + name_ + "\' (";
    for (int i = 0; i < (int) columns_.size(); i++){
        if (i > 0){
            answer += ", ";
        }
        answer += "\'" + columns_[i]->name + "\' " + EnumToString(columns_[i]->type);
    }
    answer += ");";
    return answer;
}

std::string Table::save() {
    std::string table_string;
    table_string = name_ + " " + std::to_string(columns_.size()) + " ";
    for (int i = 0; i < (int) columns_.size(); i++){
        table_string += std::to_string(columns_[i]->type) + " " + columns_[i]->name + " ";
    }
    return table_string;
}

std::string Table::EnumToString(ColumnType columnType){   //мб заменить на map
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

    void Table::insert(std::vector<std::pair<std::string, std::string>> raw) {
        std::vector<std::shared_ptr<TableCell>> cells;
        for (int i = 0; i < raw.size(); i++){
            cells.push_back(create_cell(raw[i]));
        }
        std::shared_ptr<TableRaw> tableRaw(new TableRaw(cells));
        raws_.push_back(tableRaw);
    }

    std::shared_ptr<TableCell> Table::create_cell(std::pair<std::string, std::string> cell) {
        ColumnType type;
        for (int i = 0; i < columns_.size(); i++){
            if (columns_[i]->name == cell.first){        //добавить проверку на существование
                type = columns_[i]->type;
            }
        }
        switch (type){
            case (INT):
                std::shared_ptr<IntegerTableCell> c (new IntegerTableCell(std::stoi(cell.second)));
                std::shared_ptr<TableCell> cc = c;       //госпади спаси и сохрани эти костыли
                return cc;

        }
    }

st_e::Column::Column(st_e::ColumnType type, std::string name) :
        type(type),
        name(std::move(name)) {}


}//namespace st_e
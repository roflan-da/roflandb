#pragma once

#include <memory>
#include "query_conditions.h"
#include "table_cells.h"
#include "storage_engine.h"

namespace cond {

    //ONLY FOR INT cols
    //ya ne dodumalsya kak normalno vipilit' copypaste
bool row_check(const std::string &table_name, const st_e::TableRow &row, std::shared_ptr<cond::Condition> condition) {
    switch (condition->type()) {
    case(cond::EQUAl) : {
        auto cells = row.get_cells();
        auto cols = st_e::StorageEngine::get_instance().get_table_by_name(table_name).get_ordered_columns();
        int index = 0;
        for (int i = 0; i < cells.size(); ++i) {
            if (cols[i].name == static_cast<cond::SimpleCondition*>(condition.get())->column_name()) {
                index = i;
                break;
            }
        }
        int cell_value = std::stoi(cells[index]->get_data());
        int cond_value = std::stoi(static_cast<cond::SimpleCondition*>(condition.get())->value());
        return (cell_value == cond_value);
    }
    case(cond::NOT_EQUAL) : {
        auto cells = row.get_cells();
        auto cols = st_e::StorageEngine::get_instance().get_table_by_name(table_name).get_ordered_columns();
        int index = 0;
        for (int i = 0; i < cells.size(); ++i) {
            if (cols[i].name == static_cast<cond::SimpleCondition*>(condition.get())->column_name()) {
                index = i;
                break;
            }
        }
        int cell_value = std::stoi(cells[index]->get_data());
        int cond_value = std::stoi(static_cast<cond::SimpleCondition*>(condition.get())->value());
        return (cell_value != cond_value);
    }
    case(cond::GREATER) : {
        auto cells = row.get_cells();
        auto cols = st_e::StorageEngine::get_instance().get_table_by_name(table_name).get_ordered_columns();
        int index = 0;
        for (int i = 0; i < cells.size(); ++i) {
            if (cols[i].name == static_cast<cond::SimpleCondition*>(condition.get())->column_name()) {
                index = i;
                break;
            }
        }
        int cell_value = std::stoi(cells[index]->get_data());
        int cond_value = std::stoi(static_cast<cond::SimpleCondition*>(condition.get())->value());
        return (cell_value > cond_value);
    }
    case(cond::GREATER_EQUALS) : {
        auto cells = row.get_cells();
        auto cols = st_e::StorageEngine::get_instance().get_table_by_name(table_name).get_ordered_columns();
        int index = 0;
        for (int i = 0; i < cells.size(); ++i) {
            if (cols[i].name == static_cast<cond::SimpleCondition*>(condition.get())->column_name()) {
                index = i;
                break;
            }
        }
        int cell_value = std::stoi(cells[index]->get_data());
        int cond_value = std::stoi(static_cast<cond::SimpleCondition*>(condition.get())->value());
        return (cell_value >= cond_value);
    }
    case(cond::LESS) : {
        auto cells = row.get_cells();
        auto cols = st_e::StorageEngine::get_instance().get_table_by_name(table_name).get_ordered_columns();
        int index = 0;
        for (int i = 0; i < cells.size(); ++i) {
            if (cols[i].name == static_cast<cond::SimpleCondition*>(condition.get())->column_name()) {
                index = i;
                break;
            }
        }
        int cell_value = std::stoi(cells[index]->get_data());
        int cond_value = std::stoi(static_cast<cond::SimpleCondition*>(condition.get())->value());
        return (cell_value < cond_value);
    }
    case(cond::LESS_EQUAL) : {
        auto cells = row.get_cells();
        auto cols = st_e::StorageEngine::get_instance().get_table_by_name(table_name).get_ordered_columns();
        int index = 0;
        for (int i = 0; i < cells.size(); ++i) {
            if (cols[i].name == static_cast<cond::SimpleCondition*>(condition.get())->column_name()) {
                index = i;
                break;
            }
        }
        int cell_value = std::stoi(cells[index]->get_data());
        int cond_value = std::stoi(static_cast<cond::SimpleCondition*>(condition.get())->value());
        return (cell_value <= cond_value);
    }
    case(cond::AND) : {
        return (row_check(table_name, row, static_cast<cond::ComplexCondition*>(condition.get())->left()) &&
                row_check(table_name, row, static_cast<cond::ComplexCondition*>(condition.get())->right()));
    }
    case(cond::OR) : {
        return (row_check(table_name, row, static_cast<cond::ComplexCondition*>(condition.get())->left()) ||
                row_check(table_name, row, static_cast<cond::ComplexCondition*>(condition.get())->right()));
    }
    case(cond::NOT) : {
    //WTF NOT AVAILABLE IN BETA
        return (!row_check(table_name, row, static_cast<cond::ComplexCondition*>(condition.get())->left()));
    }
    }
}

} //namespace cond
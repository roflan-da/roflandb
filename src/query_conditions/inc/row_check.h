#pragma once

#include "query_conditions.h"
#include "table.h"

namespace cond {

bool row_check(const st_e::Table &table, const st_e::TableRow &row, std::shared_ptr<cond::Condition> condition);

} //namespace cond
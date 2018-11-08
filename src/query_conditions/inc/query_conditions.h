#pragma once

#include "condition.h"

namespace cond {
enum ComplexConditionType{
    AND,
    OR,
    NOT
};



    class QueryConditions {
public:

private:
    std::string table_name_;
};

}//namespace cond
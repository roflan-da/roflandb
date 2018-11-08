#pragma once

#include "condition.h"
#include <memory>

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
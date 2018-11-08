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

        QueryConditions() = default;
        //QueryConditions()

        void type(ComplexConditionType type) { type_ = type; }
        ComplexConditionType type() const { return type_; }

        void first(std::variant<std::shared_ptr<Condition>, std::shared_ptr<QueryConditions>> first) { first_ = first; }

    private:

        ComplexConditionType type_;
        std::variant<std::shared_ptr<Condition>, std::shared_ptr<QueryConditions>> first_, second_;

    };

}//namespace cond
#pragma once

#include <utility>
#include "condition.h"
#include <memory>

namespace cond {

    enum ComplexConditionType{
        AND,
        OR,
        NOT,
        SINGLE
    };



    class QueryConditions {
    public:

        QueryConditions() = default;
        QueryConditions(ComplexConditionType type,
                std::variant<std::shared_ptr<Condition>, std::shared_ptr<QueryConditions>> first,
                std::variant<std::shared_ptr<Condition>, std::shared_ptr<QueryConditions>> second) :
                type_(type), first_(std::move(first)), second_(std::move(second)) {}

        void type(ComplexConditionType type) { type_ = type; }
        ComplexConditionType type() const { return type_; }

        void first(std::variant<std::shared_ptr<Condition>, std::shared_ptr<QueryConditions>> first) { first_ = std::move(first); }
        std::variant<std::shared_ptr<Condition>, std::shared_ptr<QueryConditions>> first() { return first_; }

        void second(std::variant<std::shared_ptr<Condition>, std::shared_ptr<QueryConditions>> second) { second_ = std::move(second); }
        std::variant<std::shared_ptr<Condition>, std::shared_ptr<QueryConditions>> second() { return second_; }

    private:

        ComplexConditionType type_ = SINGLE;
        std::variant<std::shared_ptr<Condition>, std::shared_ptr<QueryConditions>> first_, second_;

    };

}//namespace cond
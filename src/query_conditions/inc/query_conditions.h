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
                std::variant<std::shared_ptr<Condition>, std::shared_ptr<QueryConditions>> left,
                std::variant<std::shared_ptr<Condition>, std::shared_ptr<QueryConditions>> right) :
                type_(type), left_(std::move(left)), right_(std::move(right)) {}

        void type(ComplexConditionType type) { type_ = type; }
        ComplexConditionType type() const { return type_; }

        void left(std::variant<std::shared_ptr<Condition>, std::shared_ptr<QueryConditions>> left) { left_ = std::move(left); }
        std::variant<std::shared_ptr<Condition>, std::shared_ptr<QueryConditions>> left() { return left_; }

        void right(std::variant<std::shared_ptr<Condition>, std::shared_ptr<QueryConditions>> right) { right_ = std::move(right); }
        std::variant<std::shared_ptr<Condition>, std::shared_ptr<QueryConditions>> right() { return right_; }

    private:

        ComplexConditionType type_ = SINGLE;
        std::variant<std::shared_ptr<Condition>, std::shared_ptr<QueryConditions>> left_, right_;

    };

}//namespace cond
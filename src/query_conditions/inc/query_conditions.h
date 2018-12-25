#pragma once

#include <string>
#include <utility>
#include <memory>

namespace cond {

enum ConditionType{
    AND,
    OR,
    NOT,
    EQUAl,
    NOT_EQUAL,
    GREATER,
    LESS,
    GREATER_EQUALS,
    LESS_EQUAL,
    ALWAYS_TRUE
};

//HOW TO USE DIS SHIT
//auto condOR = cond::Condition();
//auto cond = cond::Condition(cond::AND, "ababaca", 12);
//std::cout << std::get<int>(cond.value());

class Condition {
public:
    Condition() = default;

    explicit Condition(ConditionType type) : type_(type) {}
    virtual ~Condition() = default;
    void type(ConditionType type) { type_ = type; }
    ConditionType type() const { return type_; }


private:
    ConditionType type_;
};

//between column and value
class SimpleCondition : public Condition {
public:
    SimpleCondition() = default;
    ~SimpleCondition() override = default ;
    SimpleCondition(ConditionType type, std::string col_name, std::string value) :
            Condition(type), column_name_(std::move(col_name)), value_(std::move(value)) {}

    void column_name(std::string name) { column_name_ = std::move(name); }
    std::string column_name() const { return column_name_; }

    void value(std::string value) { value_ = std::move(value); }
    std::string value() const { return value_; }

private:
    std::string column_name_;
    std::string value_;

};

class ComplexCondition : public Condition {
public:
    ComplexCondition() = default;
    ~ComplexCondition() override = default;
    ComplexCondition(ConditionType type, std::shared_ptr<Condition> left, std::shared_ptr<Condition> right) :
            Condition(type), left_(left), right_(right) {}

    void left(std::shared_ptr<Condition> left) { left_ = left; }
    std::shared_ptr<Condition> left() { return left_; }

    void right(std::shared_ptr<Condition> right) { right_ = right; }
    std::shared_ptr<Condition> right() { return right_; }
private:
    std::shared_ptr<Condition> left_;
    std::shared_ptr<Condition> right_;
};

class AlwaysTrueCondition : public Condition{
public:
    AlwaysTrueCondition();
    ~AlwaysTrueCondition() override = default;
};
}//namespace cond
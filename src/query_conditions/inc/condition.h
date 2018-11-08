#pragma once

#include <string>
#include <variant>
#include <utility>
#include <memory>


namespace cond{

enum ConditionType{
    AND,
    OR,
    NOT,
    EQUAl,
    NOT_EQUAL,
    MORE,
    LESS,
    MORE_EQUAL,
    LESS_EQUAL
};
    //HOW TO USE DIS SHIT
    //auto condOR = cond::Condition();
    //auto cond = cond::Condition(cond::AND, "ababaca", 12);
    //std::cout << std::get<int>(cond.value());

class Condition {
public:
    Condition() = default;
    Condition(ConditionType type, std::string col_name, std::variant<int, std::string, std::shared_ptr<Condition>> value) :
        type_(type), column_name_(std::move(col_name)), value_(std::move(value)) {}

    void column_name(std::string name) { column_name_ = name; }
    std::string column_name() const { return column_name_; }

    void type(ConditionType type) { type_ = type; }
    ConditionType type() const { return type_; }

    void value(std::variant<int, std::string, std::shared_ptr<Condition>> value) { value_ = value; }
    std::variant<int, std::string, std::shared_ptr<Condition>> value() const { return value_; }


private:

    std::string column_name_;
    ConditionType type_;
    std::variant<int, std::string, std::shared_ptr<Condition>> value_;

};

} //namespace cond
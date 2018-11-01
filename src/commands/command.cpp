#include <utility>

#include <command.h>
#include "iostream"

cmd::Command::Command() : isValid_(false){};

cmd::Command::Command(std::shared_ptr<cmd::SQLStatement> statement) : isValid_(false) {
    addStatement(std::move(statement));
};

bool cmd::Command::isValid() const {
    return isValid_;
}

std::shared_ptr<cmd::SQLStatement> cmd::Command::getStatement(int index) const {
    return getStatementsSize() > index ? statements_[index] : nullptr;
}

void cmd::Command::addStatement(std::shared_ptr<cmd::SQLStatement> statement) {
    statements_.emplace_back(statement);
}

long long int cmd::Command::getStatementsSize() const {
    return statements_.size();
}

void cmd::Command::isValid(bool isValid) {
    isValid_ = isValid;
}

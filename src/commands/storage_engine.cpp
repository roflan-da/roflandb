#include <storage_engine.h>
#include "iostream"

cmd::Command::Command() : isValid_(false){};

cmd::Command::Command(cmd::SQLStatement *statement) : isValid_(false) {
    addStatement(statement);
};

bool cmd::Command::isValid() const {
    return isValid_;
}

std::shared_ptr<cmd::SQLStatement> cmd::Command::getStatement(int index) const {
    return getStatemensSize() > index ? statements_[index] : nullptr;
}

void cmd::Command::addStatement(cmd::SQLStatement *statement) {
    statements_.emplace_back(statement);
}

long long int cmd::Command::getStatemensSize() const {
    return statements_.size();
}

void cmd::Command::isValid(bool isValid) {
    isValid_ = isValid;
}

#include <storage_engine.h>
#include "iostream"

#include "storage_engine.h"

cdm::Command::Command() : isValid_(false){};

cdm::Command::Command(cmd::SQLStatement *statement) : isValid_(false) {
    addStatement(statement);
};

bool cdm::Command::isValid() const {
    return isValid_;
}

std::shared_ptr<cmd::SQLStatement> cdm::Command::getStatement(int index) const {
    return getStatemensSize() > index ? statements_[index] : nullptr;
}

void cdm::Command::addStatement(cmd::SQLStatement *statement) {
    statements_.emplace_back(statement);
}

long long int cdm::Command::getStatemensSize() const {
    return statements_.size();
}

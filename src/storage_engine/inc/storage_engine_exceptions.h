#pragma once

#include <exception>
#include <string>

namespace st_e {

class StorageEngineException : public std::exception {
public:
    explicit StorageEngineException(const std::string& message_) : message_(message_) {}

    const char* what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};

class ColumnTypeNotExistException : public StorageEngineException {
public:
    explicit ColumnTypeNotExistException(const std::string& type)
        : StorageEngineException("Column type " + type + " doest not exist") {}
};

class TableNotExistException : public StorageEngineException {
public:
    explicit TableNotExistException(const std::string& name)
        : StorageEngineException("Table " + name + " doesn't exist") {}
};

} // namespace st_e
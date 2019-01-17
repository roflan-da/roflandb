#pragma once

#include <exception>
#include <string>

namespace st_e {

class RoflanException: public std::exception{
public:
    explicit RoflanException(const std::string& message_) : message_(message_) {}

    const char* what() const noexcept override {
        return message_.c_str();
    }

    std::string get_message()  {
        return message_;
    }

private:
    std::string message_;
};

class StorageEngineException : public RoflanException {
public:
    explicit StorageEngineException(const std::string& message_) : RoflanException(message_) {}
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

// just because
class CrutchException : public StorageEngineException {
public:
    explicit CrutchException() : StorageEngineException("You are doing something wrong.") {}
};

class IsValidException: public RoflanException {
public:
    explicit IsValidException(const std::string& message_) : RoflanException(message_) {}
};

class CreateValidException : public IsValidException {
public:
    explicit CreateValidException(const std::string& message_ = "ERROR creating table") : IsValidException(message_) {}
};

class CreateDuplicateColumnsException : public CreateValidException {
public:
    explicit CreateDuplicateColumnsException(const std::string& column_name) :
            CreateValidException("ERROR creating table: duplicate column "+column_name) {}
};

class CreateTableAlreadyExistsException : public CreateValidException {
public:
    explicit CreateTableAlreadyExistsException(const std::string& table_name) :
    CreateValidException("ERROR creating table: table alerady exists "+table_name) {}
};


class InsertValidException : public IsValidException {
public:
    explicit InsertValidException(const std::string& message_ = "ERROR inserting into table") : IsValidException(message_) {}
};

class InsertIncorrectNumberOfParametersException : public InsertValidException{
public:
    explicit InsertIncorrectNumberOfParametersException(unsigned long long expected) :
            InsertValidException("ERROR inserting into table: expected " + std::to_string(expected) + " parameters") {}
};

class InsertDuplicateColumnsException : public InsertValidException{
public:
    explicit InsertDuplicateColumnsException(std::string name) :
            InsertValidException("ERROR inserting into table: duplicate column " + name) {}
};

class InsertIncorrectColumnNameException : public InsertValidException{
public:
    explicit InsertIncorrectColumnNameException(std::string name) :
            InsertValidException("ERROR inserting into table: incorrect column " + name) {}
};

class SelectValidException : public IsValidException {
public:
    explicit SelectValidException(const std::string& message_ = "ERROR selecting from table") : IsValidException(message_) {}
};

class SelectIncorrectNumberOfColumnsException : public InsertValidException{
public:
    explicit SelectIncorrectNumberOfColumnsException(unsigned long long expected) :
            InsertValidException("ERROR selecting from table: expected " + std::to_string(expected) + " parameters") {}
};

class SelectDuplicateColumnsException : public InsertValidException{
public:
    explicit SelectDuplicateColumnsException(std::string name) :
            InsertValidException("ERROR selecting from table: duplicate column " + name) {}
};

class SelectIncorrectColumnNameException : public InsertValidException{
public:
    explicit SelectIncorrectColumnNameException(std::string name) :
            InsertValidException("ERROR selecting from table: incorrect column " + name) {}
};

class SelectTableNotExistException : public InsertValidException{
public:
    explicit SelectTableNotExistException(std::string name) :
            InsertValidException("ERROR selecting from table: table " + name + " doesn't exist") {}
};

class SelectConditionsNotValidException : public InsertValidException{
public:
    explicit SelectConditionsNotValidException() :
            InsertValidException("ERROR selecting from table: incorrect conditions") {}
};

class DropValidException : public IsValidException {
public:
    explicit DropValidException(const std::string& message_ = "ERROR dropping table") : IsValidException(message_) {}
};

class DropTableNotExistException : public InsertValidException{
public:
    explicit DropTableNotExistException(std::string name) :
            InsertValidException("ERROR dropping table: table " + name + " doesn't exist") {}
};

class ShowValidException : public IsValidException {
public:
    explicit ShowValidException(const std::string& message_ = "ERROR showing table") : IsValidException(message_) {}
};

class ShowTableNotExistException : public InsertValidException{
public:
    explicit ShowTableNotExistException(std::string name) :
            InsertValidException("ERROR dropping table: table " + name + " doesn't exist") {}
};
} // namespace st_e
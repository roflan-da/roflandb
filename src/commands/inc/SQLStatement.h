#ifndef ROFLANDB_SQLSTATEMENTS_H
#define ROFLANDB_SQLSTATEMENTS_H

enum statements_type{
    CREATE_TABLE,
    SHOW_CREATE_TABLE
};

class SQLStatement {
public:
    explicit SQLStatement(statements_type type): type_(type) {};

    statements_type type();
private:
    statements_type type_;
};


#endif //ROFLANDB_SQLSTATEMENTS_H

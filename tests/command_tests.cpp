#include "catch.hpp"
#include <command.h>
#include <statements.h>
#include <string>

TEST_CASE("Constructor tests") {

    SECTION("trivial") {
        cmd::Command ex1;
        REQUIRE_FALSE(ex1.isValid());
        REQUIRE(ex1.getStatementsSize() == 0);
    }

    SECTION("construct with statement") {
        cmd::SQLStatement sql_satement;
        cmd::CreateStatement create_statement;
        std::string name = "table_name";
        cmd::Command ex1(std::make_shared<cmd::SQLStatement>(sql_satement));
        cmd::Command ex2(std::make_shared<cmd::SQLStatement>(create_statement));
        REQUIRE_FALSE(ex1.isValid());
        REQUIRE_FALSE(ex2.isValid());
        REQUIRE(ex1.getStatementsSize() == 1);
        REQUIRE(ex2.getStatementsSize() == 1);
    }

    SECTION("add statements"){
        cmd::CreateStatement create_statement;
        cmd::Command ex2(std::make_shared<cmd::SQLStatement>(create_statement));
        REQUIRE(ex2.getStatementsSize() == 1);
        ex2.addStatement(std::make_shared<cmd::SQLStatement>(create_statement));
        REQUIRE(ex2.getStatementsSize() == 2);
        for (int i = 0; i < 10; ++i) {
            ex2.addStatement(std::make_shared<cmd::SQLStatement>(create_statement));
        }
        REQUIRE(ex2.getStatementsSize() == 12);
    }

    SECTION("isValid change"){
        cmd::CreateStatement create_statement;
        cmd::Command ex2;
        ex2.isValid(true);
        REQUIRE(ex2.isValid());
        ex2.isValid(false);
        REQUIRE_FALSE(ex2.isValid());
    }

    SECTION("isValid change"){
        cmd::Command ex2;
        ex2.isValid(true);
        REQUIRE(ex2.isValid());
        ex2.isValid(false);
        REQUIRE_FALSE(ex2.isValid());
    }

    SECTION("get statement"){
        cmd::CreateStatement create_statement;
        cmd::Command ex2(std::make_shared<cmd::SQLStatement>(create_statement));
        ex2.isValid(true);
        REQUIRE(ex2.isValid());
        REQUIRE(ex2.getStatement(0).get()->type() == cmd::CREATE_TABLE);
    }
}
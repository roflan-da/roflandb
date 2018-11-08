#include "catch.hpp"
#include <command.h>
#include <statements.h>
#include <string>

TEST_CASE("Constructor tests") {

    SECTION("trivial") {
        cmd::Command ex1;
        REQUIRE_FALSE(ex1.is_valid());
    }

    SECTION("construct with statement") {
        cmd::SQLStatement sql_satement;
        cmd::CreateStatement create_statement;
        std::string name = "table_name";
        cmd::Command ex1(std::make_shared<cmd::SQLStatement>(sql_satement));
        cmd::Command ex2(std::make_shared<cmd::CreateStatement>(create_statement));
        REQUIRE_FALSE(ex1.is_valid());
        REQUIRE_FALSE(ex2.is_valid());
    }

    SECTION("add statements"){
        cmd::CreateStatement create_statement;
        cmd::Command ex2(std::make_shared<cmd::CreateStatement>(create_statement));
        ex2.add_statement(std::make_shared<cmd::CreateStatement>(create_statement));
        for (int i = 0; i < 10; ++i) {
            ex2.add_statement(std::make_shared<cmd::CreateStatement>(create_statement));
        }
    }

    SECTION("is_valid change"){
        cmd::CreateStatement create_statement;
        cmd::Command ex2;
        ex2.is_valid(true);
        REQUIRE(ex2.is_valid());
        ex2.is_valid(false);
        REQUIRE_FALSE(ex2.is_valid());
    }

    SECTION("is_valid change"){
        cmd::Command ex2;
        ex2.is_valid(true);
        REQUIRE(ex2.is_valid());
        ex2.is_valid(false);
        REQUIRE_FALSE(ex2.is_valid());
    }

    SECTION("get statement"){
        cmd::CreateStatement create_statement;
        cmd::Command ex2(std::make_shared<cmd::CreateStatement>(create_statement));
        ex2.is_valid(true);
        REQUIRE(ex2.is_valid());
    }
}
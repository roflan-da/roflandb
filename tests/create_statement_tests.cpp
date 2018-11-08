#include "catch.hpp"
#include <statements.h>
#include <string>

TEST_CASE("create_statements tests") {

    SECTION("simple create") {
        cmd::CreateStatement create_statement;
        REQUIRE(create_statement.get_table_name() == "");
        REQUIRE(create_statement.type() == cmd::CREATE_TABLE);
    }

    SECTION("create with args") {
        std::string table_name = "name1";
        cmd::CreateStatement create_statement(table_name);
        REQUIRE(create_statement.get_table_name() == table_name);
        REQUIRE(create_statement.type() == cmd::CREATE_TABLE);
        REQUIRE(create_statement.get_columns().size() == 0);
    }

    SECTION("create with table_name and add columns") {
        std::string table_name = "name1";
        cmd::CreateStatement create_statement(table_name);
        REQUIRE(create_statement.get_table_name() == table_name);
        REQUIRE(create_statement.type() == cmd::CREATE_TABLE);
        REQUIRE(create_statement.get_columns().size() == 0);

        st_e::Column col1(st_e::INT, "col_name1");
        st_e::Column col2(st_e::INT, "col_name2");
        st_e::Column col3(st_e::INT, "col_name3");
        create_statement.add_column(std::make_shared<st_e::Column>(col1));
        create_statement.add_column(std::make_shared<st_e::Column>(col2));
        create_statement.add_column(std::make_shared<st_e::Column>(col3));

        REQUIRE(create_statement.get_columns().size() == 3);
        auto mem = create_statement.get_columns();
        REQUIRE(mem[0].get()->type == st_e::INT);
        REQUIRE(mem[0].get()->name == "col_name1");
        REQUIRE(mem[1].get()->type == st_e::INT);
        REQUIRE(mem[1].get()->name == "col_name2");
        REQUIRE(mem[2].get()->type == st_e::INT);
        REQUIRE(mem[2].get()->name == "col_name3");
    }

}

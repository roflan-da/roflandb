#include "catch.hpp"
#include <statements.h>
#include <string>
#include "driver.h"


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

TEST_CASE("create statement using parser"){

    SECTION("case sensivity"){
        std::string query = "CREATE TABLE a(col1 INT);";
        roflan_parser::Driver parser_driver;
        std::string error_message;
        REQUIRE (parser_driver.parse_string(query, error_message));
        auto res = parser_driver.sql_parser_result.get();
        REQUIRE(res->is_valid());
        REQUIRE(res->get_statements().size() == 1);
        REQUIRE(res->get_statements()[0].get()->type() == cmd::CREATE_TABLE);
//        REQUIRE(parser_driver.sql_parser_result.get()->get_statements()[0].get()->get_table_name() == "a");
        //no getter for table_name and columns
    }

    SECTION("table with 1 column"){

    }
}

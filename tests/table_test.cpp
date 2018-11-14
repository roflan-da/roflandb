#include <driver.h>
#include <storage_engine.h>
#include "catch.hpp"
#include "table.h"


TEST_CASE("structColumn") {

    SECTION("trivial") {
        auto col = st_e::Column(st_e::STRING, "test");
        REQUIRE(col.name == "test");
        REQUIRE(col.type == st_e::STRING);

    }

}

TEST_CASE("Integer Table Cell") {

    SECTION("trivial") {
        st_e::IntegerTableCell intcol(5);
        REQUIRE(intcol.get_data() == "5");
    }


    SECTION("intmax") {
        st_e::IntegerTableCell intcol(INT_MAX);
        REQUIRE(intcol.get_data() == std::to_string(INT_MAX));
    }

}

TEST_CASE("TableBuilder") {

    SECTION("trivial") {
        st_e::TableBuilder tb("ababaca");
        std::vector<std::shared_ptr<st_e::Column>> cols;
        cols.emplace_back(std::make_shared<st_e::Column>(st_e::INT, "intcol"));
        cols.emplace_back(std::make_shared<st_e::Column>(st_e::STRING, "strcol"));
        tb.set_columns(cols);
        auto table = tb.build();

    }

}

TEST_CASE("Table") {

    st_e::TableBuilder tb("ababaca");
    std::vector<std::shared_ptr<st_e::Column>> cols;
    cols.emplace_back(std::make_shared<st_e::Column>(st_e::INT, "intcol"));
    cols.emplace_back(std::make_shared<st_e::Column>(st_e::STRING, "strcol"));
    tb.set_columns(cols);
    auto table = tb.build();

    SECTION("get_sql") {
        REQUIRE(table->get_sql() == "CREATE TABLE \'ababaca\' (\'intcol\' INT, \'strcol\' STRING);");
    }

    SECTION("get_name") {
        REQUIRE(table->get_name() == "ababaca");
    }

    SECTION("EnumToString") {
        REQUIRE(table->enum_to_string(st_e::INT) == "INT");
        REQUIRE(table->enum_to_string(st_e::STRING) == "STRING");
        REQUIRE(table->enum_to_string(st_e::CHAR) == "CHAR");
        REQUIRE(table->enum_to_string(st_e::TEXT) == "TEXT");
    }

    SECTION("create_cell") {

    }

    SECTION("insert") {

    }

    SECTION("save") {

    }

    SECTION("load") {

    }
}

TEST_CASE("Parser"){
    roflan_parser::Driver parser_driver;
    st_e::StorageEngine storage_engine;
    std::string query = "CREATE TABLE a(col1 INT);"
                        "INSERT INTO a VALUES(1488);"
                        "INSERT INTO a VALUES(1337);"
                        "SELECT * FROM a;";
    std::string error_message;
    REQUIRE(parser_driver.parse_string(query, error_message));
    parser_driver.sql_parser_result->execute(storage_engine);


}
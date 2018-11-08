#include "catch.hpp"
#include "table.h"

TEST_CASE("EnumToString") {

    SECTION("INT") {
        REQUIRE(st_e::EnumToString(st_e::INT) == "INT");
    }

    SECTION("Other") {
        REQUIRE(st_e::EnumToString(st_e::STRING) == "");
    }


}

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

TEST_CASE("Table") {

//    SECTION("getSQL_trivial") {
//        st_e::TableBuilder tb("mems");
//        tb.add_column(st_e::INT, "Test");
//        st_e::Table t = tb.build();
//        REQUIRE(t.get_sql() == "CREATE TABLE \'mems\' (\'Test\' INT);");
//    }
//
//    SECTION("getSQL_2_st_e::INT") {
//        st_e::TableBuilder tb("mems");
//        tb.add_column(st_e::INT, "Test");
//        tb.add_column(st_e::INT, "Test2");
//        st_e::Table t = tb.build();
//        REQUIRE(t.get_sql() == "CREATE TABLE \'mems\' (\'Test\' INT, \'Test2\' INT);");
//    }

}

TEST_CASE("Table") {

//    SECTION("getSQL_trivial") {
//        st_e::TableBuilder tb("mems");
//        tb.add_column(st_e::INT, "Test");
//        st_e::Table t = tb.build();
//        REQUIRE(t.get_sql() == "CREATE TABLE \'mems\' (\'Test\' INT);");
//    }
//
//    SECTION("getSQL_2_st_e::INT") {
//        st_e::TableBuilder tb("mems");
//        tb.add_column(st_e::INT, "Test");
//        tb.add_column(st_e::INT, "Test2");
//        st_e::Table t = tb.build();
//        REQUIRE(t.get_sql() == "CREATE TABLE \'mems\' (\'Test\' INT, \'Test2\' INT);");
//    }

}
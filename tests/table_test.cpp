#include "catch.hpp"
#include "table.h"


TEST_CASE("IntegerColumn") {

    SECTION("trivial") {
        st_e::IntegerColumn intcol("Test");
    }


}

TEST_CASE("Table") {

    SECTION("getSQL_trivial") {
        st_e::TableBuilder tb("mems");
        tb.add_column(st_e::INT, "Test");
        st_e::Table t = tb.build();
        REQUIRE(t.get_sql() == "CREATE TABLE \'mems\' (\'Test\' INT);");
    }

    SECTION("getSQL_2_st_e::INT") {
        st_e::TableBuilder tb("mems");
        tb.add_column(st_e::INT, "Test");
        tb.add_column(st_e::INT, "Test2");
        st_e::Table t = tb.build();
        REQUIRE(t.get_sql() == "CREATE TABLE \'mems\' (\'Test\' INT, \'Test2\' INT);");
    }

}
#include "catch.hpp"
#include <table.h>


TEST_CASE("IntegerColumn") {

    SECTION("trivial") {
        IntegerColumn intcol("Test");
        REQUIRE(intcol.getName() == "Test");
        REQUIRE(intcol.getTypeName() == INT);
    }


}

TEST_CASE("Table") {

    SECTION("getSQL_trivial") {
        TableBuilder tb("mems");
        tb.addColumn(INT, "Test");
        Table t = tb.build();
        REQUIRE(t.getSql() == "CREATE TABLE \'mems\' (\'Test\' INT);");
    }

    SECTION("getSQL_2_INT") {
        TableBuilder tb("mems");
        tb.addColumn(INT, "Test");
        tb.addColumn(INT, "Test2");
        Table t = tb.build();
        REQUIRE(t.getSql() == "CREATE TABLE \'mems\' (\'Test\' INT, \'Test2\' INT);");
    }

}
#include "catch.hpp"
#include <table.h>


TEST_CASE("IntegerColumn") {

    SECTION("trivial") {
        IntegerColumn intcol("Test");
        REQUIRE(intcol.getName() == "Test");
        REQUIRE(intcol.getTypeName() == "INT");
    }


}

TEST_CASE("TableBuilder") {

    SECTION("getTableName") {
        TableBuilder tb("mems");
        REQUIRE(tb.getTableName() == "mems");
    }

    SECTION("getColumns_0") {
        TableBuilder tb("mems");
        REQUIRE(tb.getColumns().size() == 0);
    }

    SECTION("getColumns_INT_1") {
        TableBuilder tb("mems");
        tb.addColumn("INT", "Test");
        REQUIRE(tb.getColumns().size() == 1);
        REQUIRE(tb.getColumns()[0]->getTypeName() == "INT");
        REQUIRE(tb.getColumns()[0]->getName() == "Test");
    }

    SECTION("getColumns_WRONG_1") {
        TableBuilder tb("mems");
        tb.addColumn("abracadabra", "Test");
        REQUIRE(tb.getColumns().size() == 0);
    }

    SECTION("getColumns_INT_MAX_INT") {
        TableBuilder tb("mems");
        for (int i = 0; i < INT_MAX; ++i) {
            tb.addColumn("INT", "Test" + std::to_string(i));
        }
        std::vector<std::shared_ptr<Column>> columns(tb.getColumns());
        REQUIRE(tb.getColumns().size() == INT_MAX);
        for (int i = 0; i < INT_MAX; ++i) {
            REQUIRE(columns[i]->getTypeName() == "INT");
            REQUIRE(columns[i]->getName() == "Test" + std::to_string(i));

        }

    }



}

TEST_CASE("Table") {

    SECTION("getSQL_trivial") {
        TableBuilder tb("mems");
        tb.addColumn("INT", "Test");
        Table t(tb);
        REQUIRE(t.getSql() == "CREATE TABLE \'mems\' (\'Test\' INT);");
    }

    SECTION("getSQL_2_INT") {
        TableBuilder tb("mems");
        tb.addColumn("INT", "Test");
        tb.addColumn("INT", "Test2");
        Table t(tb);
        REQUIRE(t.getSql() == "CREATE TABLE \'mems\' (\'Test\' INT, \'Test2\' INT);");
    }

}
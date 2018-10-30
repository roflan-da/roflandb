#include "catch.hpp"
#include "table.h"


TEST_CASE("IntegerColumn") {

    SECTION("trivial") {
        TableBuilder tableBuilder("Kektable");

        IntegerColumn intcol("Test");
        CHECK(intcol.getName() == "Test");
        CHECK(intcol.getTypeName() == "INT");
    }

}

TEST_CASE("Table") {

}

TEST_CASE("TableBuilder") {

}
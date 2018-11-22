#define SET_PRIVATE_AS_PUBLIC

#include "catch.hpp"
#include "driver.h"
#include "storage_engine.h"

bool validate_query(const std::string &query) {
    roflan_parser::Driver parser_driver;
    std::__cxx11::string error_message;
    REQUIRE(parser_driver.parse_string(query, error_message));
    bool res = true;
    for (const auto& statement: parser_driver.sql_parser_result->statements_){
        if (!statement->is_valid()){
            res = false;
            break;
        };
    }
    return res;
}

TEST_CASE("Insert Statement Validation"){
    SECTION("trivial"){
        std::vector<std::string> queries {"CREATE TABLE a (c1 INT);",
                                           "INSERT a(c1) VALUES(1);",
                                           "INSERT INTO a(c1) VALUES(2);",
                                           "INSERT INTO a(c2) VALUES(3);"};
        std::vector <int> validator_answers {1,1,1,0};
        for (int i = 0; i < queries.size(); ++i){
            REQUIRE(validate_query(queries[i]) == validator_answers[i]);
        }
    }
}
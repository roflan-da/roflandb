#include <storage_engine_exceptions.h>
#include "catch.hpp"
#include "driver.h"
#include "storage_engine.h"
#include "inc/dtl/dtl.hpp"
#include "row_check.h"

bool compare(const std::string &s1, const std::string &s2) {
    dtl::Diff<char, std::string> d(s1, s2);
    d.compose();
    return bool(!d.getEditDistance());
}

bool test_statement(const std::string &query, const std::string &output) {
    std::string cleanoutput = output;
    cleanoutput.erase(remove_if(cleanoutput.begin(), cleanoutput.end(), isspace), cleanoutput.end());
    roflan_parser::Driver parser_driver;
    std::string error_message;
    try{
        parser_driver.parse_string("DROP TABLE a;");
        parser_driver.sql_parser_result->execute();
    } catch(...){}
    parser_driver.parse_string(query, error_message);
    parser_driver.sql_parser_result->execute();
    std::string realoutput(parser_driver.sql_parser_result->get_messages());
    realoutput.erase(remove_if(realoutput.begin(), realoutput.end(), isspace), realoutput.end());
    //std::cout << "TEST OUTPUT " << output << std::endl;
    //std::cout << "REAL OUTPUT " << parser_driver.sql_parser_result->get_messages() << std::endl;
    //std::cout << "RESULT " << parser_driver.result << std::endl;
    return (compare(cleanoutput, realoutput));
}

std::string repeat(int n, std::string s) {
    std::ostringstream os;
    for (int i = 0; i < n; i++)
        os << s;
    return os.str();
}

TEST_CASE("create, insert, select *"){
    REQUIRE(test_statement("CREATE TABLE a(c1 INT, c2 INT);"
                       "INSERT a(c1,c2) VALUES (12,14);"
                       "SELECT * FROM a;"
                       "DROP TABLE a;",
                       "|c1|c2|\n"
                       "|12|14|"));
}


TEST_CASE("create, insert, select column_names") {
    REQUIRE(test_statement("CREATE TABLE a(c1 INT, c2 INT);"
                       "INSERT a(c1,c2) VALUES (12,14);"
                       "SELECT c1,c2 FROM a;"
                       "DROP TABLE a;",
                       "|c1|c2|\n"
                       "|12|14|"));
}

TEST_CASE("select formatting"){
    REQUIRE(test_statement("CREATE TABLE a(c1 INT, c2 INT, column3 INT);"
                       "INSERT a(c1,c2,column3) VALUES (12,14,0);"
                       "INSERT a(c1,c2,column3) VALUES (1,1746,177);"
                       "SELECT c1,c2,column3 FROM a;"
                       "DROP TABLE a;",
                       "|c1|  c2|column3|\n"
                       "|12|  14|      0|\n"
                       "| 1|1746|    177|"));
}

TEST_CASE("insert not all columns","[.]"){
    CHECK_THROWS(test_statement("CREATE TABLE a(c1 INT, c2 INT, c3 INT);"
                              "INSERT a(c1,c2) VALUES (12,14);"
                              "INSERT a(c1,c2,c3) VALUES (1,1746,177);"
                              "SELECT c1,c2,c3 FROM a;"
                              "DROP TABLE a;",
                              "|c1|  c2| c3|\n"
                              "|12|  14|177|\n"
                              "| 1|1746|   |"));
}

TEST_CASE("select not all columns","[.]"){
    CHECK_THROWS(test_statement("CREATE TABLE a(c1 INT, c2 INT, c3 INT);"
                              "INSERT a(c1,c2) VALUES (12,14);"
                              "INSERT a(c1,c2,c3) VALUES (1,1746,177);"
                              "SELECT c1,c3 FROM a;"
                              "DROP TABLE a;",
                              "|c1| c3|\n"
                              "|12|177|\n"
                              "| 1|   |"));
}

TEST_CASE("insert into"){
    REQUIRE(test_statement("CREATE TABLE a(c1 INT, c2 INT);"
                       "INSERT INTO a(c2,c1) VALUES (12,14);"
                       "SELECT c1,c2 FROM a;"
                       "DROP TABLE a;",
                       "|c1|c2|\n"
                       "|14|12|"));
}

TEST_CASE("insert with columns inversion","[.]"){
    CHECK(test_statement("CREATE TABLE a(c1 INT, c2 INT, c3 INT);"
                       "INSERT a(c2,c1) VALUES (12,14);"
                       "INSERT a(c3,c1,c2) VALUES (12,14,13);"
                       "SELECT * FROM a;"
                       "DROP TABLE a;",
                       "|c1|c2|c3|\n"
                       "|12|14|12|\n"
                       "|14|13|  |"));
}

TEST_CASE("erase table before creation"){
    REQUIRE_THROWS(test_statement("CREATE TABLE a(c1 INT, c2 INT, column3 INT);"
                              "INSERT a(c1,c2,column3) VALUES (12,14,0);"
                              "INSERT a(c1,c2,column3) VALUES (1,1746,177);"
                              "SELECT c1,c2,c3 FROM a;"
                              "DROP TABLE a;",//c3 has to be undefined??
                              "SOME ERROR MESSAGE"));
}

//TEST_CASE("big insert"){
//    roflan_parser::Driver parser_driver;
//    std::string error_message;
//
//    parser_driver.parse_string("create table test(id int, phone int);", error_message);
//    parser_driver.sql_parser_result->execute();
//
//    for (int i = 1; i < 20000; ++i) {
//        auto k = i - 1;
//        parser_driver.parse_string("insert into test(id, phone) values (" + std::to_string(i)+ ", " + std::to_string(k)+ ");", error_message);
//        parser_driver.sql_parser_result->execute();
//    }
//}

TEST_CASE("huge insert"){
    std::string single_insert = "INSERT a(c1,c2,c3) VALUES (1,2,3);";
    std::string single_select_output = "| 1| 2| 3|\n";
    REQUIRE(test_statement("CREATE TABLE a(c1 INT, c2 INT, c3 INT);" + repeat(1000, single_insert) + "SELECT * FROM a;DROP TABLE a;",
                            "|c1|c2|c3|\n" + repeat(1000, single_select_output)));
}

TEST_CASE("insert > 64k"){
    std::string single_insert = "INSERT a(c1,c2,c3) VALUES (1,2,3);";
    std::string single_select_output = "| 1| 2| 3|\n";
    REQUIRE(test_statement("CREATE TABLE a(c1 INT, c2 INT, c3 INT);" + repeat(50000, single_insert) + "SELECT * FROM a;DROP TABLE a;",
                           "|c1|c2|c3|\n" + repeat(50000, single_select_output)));
}

TEST_CASE("negative ints"){
    REQUIRE(test_statement("CREATE TABLE a(c1 INT, c2 INT);"
                           "INSERT INTO a(c2,c1) VALUES (-12,14);"
                           "SELECT c1,c2 FROM a;"
                           "DROP TABLE a;",
                           "|c1| c2|\n"
                           "|14|-12|"));
}

TEST_CASE("drop table"){
    REQUIRE_THROWS(test_statement("CREATE TABLE a(c1 INT, c2 INT);"
                                  "INSERT INTO a(c2,c1) VALUES (12,14);"
                                  "DROP table a;"
                                  "SELECT c1,c2 FROM a;",
                                  "SOME ERROR MESSAGE"));
}

TEST_CASE("drop table does not drop all tables"){
    REQUIRE(test_statement("CREATE TABLE a(c1 INT, c2 INT);"
                           "INSERT INTO a(c2,c1) VALUES (-12,14);"
                           "CREATE TABLE b(c1 INT, c2 INT);"
                           "INSERT INTO b(c2,c1) VALUES (-12,14);"
                           "DROP TABLE a;"
                           "SELECT * FROM b;"
                           "DROP TABLE b;",
                           "|c1| c2|\n"
                           "|14|-12|"));
}

TEST_CASE("create table after drop"){
    REQUIRE(test_statement("CREATE TABLE a(c1 INT, c2 INT);"
                       "INSERT INTO a(c2,c1) VALUES (12,14);"
                       "DROP table a;"
                       "CREATE TABLE a(c1 INT, c2 INT);"
                       "INSERT INTO a(c2,c1) VALUES (12,14);"
                       "SELECT c1,c2 FROM a;",
                       "|c1|c2|\n"
                       "|14|12|"));
}

std::string execute_query(const std::string &query) {
    std::string error_message;
    roflan_parser::Driver parser_driver;
    parser_driver.parse_string(query, error_message);
    parser_driver.sql_parser_result->execute();
    return error_message;
}

TEST_CASE("Trivial testing of row_check","[.]"){
    execute_query("CREATE TABLE a(c1 INT, c2 INT); INSERT INTO a(c1,c2) VALUES(1,2);");
    std::vector<std::shared_ptr<st_e::TableCell>> cells;
    cells.push_back(std::make_shared<st_e::IntegerTableCell>(st_e::IntegerTableCell(1)));
    cells.push_back(std::make_shared<st_e::IntegerTableCell>(st_e::IntegerTableCell(2)));
    st_e::TableRow row(cells, false);
    auto cond = std::make_shared<cond::SimpleCondition>(cond::EQUAl,"c1","1");
    REQUIRE(cond::row_check(st_e::StorageEngine::get_instance().get_table_by_name("a"), row, cond));
}

TEST_CASE("Trivial testing of row_check where condition is not true","[.]"){
    execute_query("CREATE TABLE a(c1 INT, c2 INT); INSERT INTO a(c1,c2) VALUES(1,2);");
    std::vector<std::shared_ptr<st_e::TableCell>> cells;
    cells.push_back(std::make_shared<st_e::IntegerTableCell>(st_e::IntegerTableCell(1)));
    cells.push_back(std::make_shared<st_e::IntegerTableCell>(st_e::IntegerTableCell(2)));
    st_e::TableRow row(cells, false);
    auto cond = std::make_shared<cond::SimpleCondition>(cond::EQUAl,"c1","123");
    REQUIRE_FALSE(cond::row_check(st_e::StorageEngine::get_instance().get_table_by_name("a"), row, cond));
}

TEST_CASE("LESS condition","[.]"){
    execute_query("CREATE TABLE a(c1 INT, c2 INT); INSERT INTO a(c1,c2) VALUES(1,2,3);");
    std::vector<std::shared_ptr<st_e::TableCell>> cells;
    cells.push_back(std::make_shared<st_e::IntegerTableCell>(st_e::IntegerTableCell(1)));
    cells.push_back(std::make_shared<st_e::IntegerTableCell>(st_e::IntegerTableCell(2)));
    st_e::TableRow row(cells, false);
    auto cond = std::make_shared<cond::SimpleCondition>(cond::LESS,"c2","123");
    REQUIRE(cond::row_check(st_e::StorageEngine::get_instance().get_table_by_name("a"), row, cond));
}

TEST_CASE("LESS_EQUAL condition","[.]"){
    execute_query("CREATE TABLE a(c1 INT, c2 INT); INSERT INTO a(c1,c2) VALUES(1,2,3);");
    std::vector<std::shared_ptr<st_e::TableCell>> cells;
    cells.push_back(std::make_shared<st_e::IntegerTableCell>(st_e::IntegerTableCell(1)));
    cells.push_back(std::make_shared<st_e::IntegerTableCell>(st_e::IntegerTableCell(2)));
    st_e::TableRow row(cells, false);
    auto cond = std::make_shared<cond::SimpleCondition>(cond::LESS_EQUAL,"c2","2");
    REQUIRE(cond::row_check(st_e::StorageEngine::get_instance().get_table_by_name("a"), row, cond));
}

TEST_CASE("GREATER condition","[.]"){
    execute_query("CREATE TABLE a(c1 INT, c2 INT); INSERT INTO a(c1,c2) VALUES(1,2,3);");
    std::vector<std::shared_ptr<st_e::TableCell>> cells;
    cells.push_back(std::make_shared<st_e::IntegerTableCell>(st_e::IntegerTableCell(1)));
    cells.push_back(std::make_shared<st_e::IntegerTableCell>(st_e::IntegerTableCell(2)));
    st_e::TableRow row(cells, false);
    auto cond = std::make_shared<cond::SimpleCondition>(cond::GREATER,"c2","0");
    REQUIRE(cond::row_check(st_e::StorageEngine::get_instance().get_table_by_name("a"), row, cond));
}

TEST_CASE("GREATER_OR_EQUAL condition","[.]"){
    execute_query("CREATE TABLE a(c1 INT, c2 INT); INSERT INTO a(c1,c2) VALUES(1,2,3);");
    std::vector<std::shared_ptr<st_e::TableCell>> cells;
    cells.push_back(std::make_shared<st_e::IntegerTableCell>(st_e::IntegerTableCell(1)));
    cells.push_back(std::make_shared<st_e::IntegerTableCell>(st_e::IntegerTableCell(2)));
    st_e::TableRow row(cells, false);
    auto cond = std::make_shared<cond::SimpleCondition>(cond::GREATER_EQUALS,"c2","2");
    REQUIRE(cond::row_check(st_e::StorageEngine::get_instance().get_table_by_name("a"), row, cond));
}

TEST_CASE("Integers less than 0","[.]"){
    execute_query("CREATE TABLE a(c1 INT, c2 INT); INSERT INTO a(c1,c2) VALUES(-1,-2,-3);");
    std::vector<std::shared_ptr<st_e::TableCell>> cells;
    cells.push_back(std::make_shared<st_e::IntegerTableCell>(st_e::IntegerTableCell(1)));
    cells.push_back(std::make_shared<st_e::IntegerTableCell>(st_e::IntegerTableCell(2)));
    st_e::TableRow row(cells, false);
    auto cond = std::make_shared<cond::SimpleCondition>(cond::LESS,"c2","123");
    REQUIRE(cond::row_check(st_e::StorageEngine::get_instance().get_table_by_name("a"), row, cond));
}

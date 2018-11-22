#include "catch.hpp"
#include "driver.h"
#include "storage_engine.h"
#include "inc/dtl/dtl.hpp"

long long int compare(const std::string& s1, const std::string& s2){
    dtl::Diff<char, std::string> d(s1, s2);
    d.compose();
    return  d.getEditDistance();
}

int test_statement(const std::string& query, const std::string& output){
    std::string cleanquery = query;
    std::string cleanoutput = output;
    cleanquery.erase(remove_if(cleanquery.begin(), cleanquery.end(), isspace), cleanquery.end());
    cleanoutput.erase(remove_if(cleanoutput.begin(), cleanoutput.end(), isspace), cleanoutput.end());
    roflan_parser::Driver parser_driver;
    std::string error_message;
    parser_driver.parse_string(query, error_message);
    parser_driver.sql_parser_result->execute();
//    std::cout << "MESSAGES " << parser_driver.sql_parser_result->get_messages() << std::endl;
//    std::cout << "RESULT " << parser_driver.result << std::endl;
    REQUIRE(compare(cleanoutput,parser_driver.sql_parser_result->get_messages()));
}

TEST_CASE("create insert select") {
    test_statement("CREATE TABLE a(c1 INT, c2 INT);"
                   "INSERT a(c1,c2) VALUES (12,14);"
                   "SELECT c1,c2 FROM a;",
                   "INSERT INTO a SUCCESSFUL.\n"
                   "|c1|c2|\n"
                   "|12|14|");
    test_statement("CREATE TABLE a(c1 INT, c2 INT, c3 INT);"
                   "INSERT a(c1,c2) VALUES (12,14);"
                   "INSERT a(c1,c2,c3) VALUES (1,1746,177);"
                   "SELECT c1,c2,c3 FROM a;",
                   "INSERT INTO a SUCCESSFUL.\n"
                   "INSERT INTO a SUCCESSFUL.\n"
                   "|c1|c2|c3\n"
                   "|12|  14|177"
                   "| 1|1746|   ");
}
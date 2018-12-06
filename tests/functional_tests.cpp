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
    //std::cout << "MESSAGES " << parser_driver.sql_parser_result->get_messages() << std::endl;
    //std::cout << "RESULT " << parser_driver.result << std::endl;
    REQUIRE(compare(cleanoutput,parser_driver.sql_parser_result->get_messages()));
}

std::string repeat(int n, std::string s) {
    std::ostringstream os;
    for(int i = 0; i < n; i++)
        os << s;
    return os.str();
}

TEST_CASE("create insert select") {

    SECTION("create, insert, select *"){
        test_statement("CREATE TABLE a(c1 INT, c2 INT);"
                       "INSERT a(c1,c2) VALUES (12,14);"
                       "SELECT * FROM a;",
                       "|c1|c2|\n"
                       "|12|14|");
    }


    SECTION("create, insert, select column_names") {
        test_statement("CREATE TABLE a(c1 INT, c2 INT);"
                       "INSERT a(c1,c2) VALUES (12,14);"
                       "SELECT c1,c2 FROM a;",
                       "|c1|c2|\n"
                       "|12|14|");
    }

    SECTION("select formatting"){
        test_statement("CREATE TABLE a(c1 INT, c2 INT, column3 INT);"
                       "INSERT a(c1,c2,column3) VALUES (12,14,0);"
                       "INSERT a(c1,c2,column3) VALUES (1,1746,177);"
                       "SELECT c1,c2,column3 FROM a;",
                       "INSERT INTO a SUCCESSFUL.\n"
                       "INSERT INTO a SUCCESSFUL.\n"
                       "|c1|  c2|column3|\n"
                       "|12|  14|      0|\n"
                       "| 1|1746|    177|");
    }

    SECTION("insert not all columns"){
        test_statement("CREATE TABLE a(c1 INT, c2 INT, c3 INT);"
                       "INSERT a(c1,c2) VALUES (12,14);"
                       "INSERT a(c1,c2,c3) VALUES (1,1746,177);"
                       "SELECT c1,c2,c3 FROM a;",
                       "INSERT INTO a SUCCESSFUL.\n"
                       "INSERT INTO a SUCCESSFUL.\n"
                       "|c1|  c2| c3|\n"
                       "|12|  14|177|\n"
                       "| 1|1746|   |");
    }

    SECTION("select not all columns"){
        test_statement("CREATE TABLE a(c1 INT, c2 INT, c3 INT);"
                       "INSERT a(c1,c2) VALUES (12,14);"
                       "INSERT a(c1,c2,c3) VALUES (1,1746,177);"
                       "SELECT c1,c3 FROM a;",
                       "INSERT INTO a SUCCESSFUL.\n"
                       "INSERT INTO a SUCCESSFUL.\n"
                       "|c1| c3|\n"
                       "|12|177|\n"
                       "| 1|   |");
    }

    SECTION("insert into"){
        test_statement("CREATE TABLE a(c1 INT, c2 INT);"
                       "INSERT INTO a(c2,c1) VALUES (12,14);"
                       "SELECT c1,c2 FROM a;",
                       "INSERT INTO a SUCCESSFUL.\n"
                       "|c1|c2|\n"
                       "|12|14|");
    }

    SECTION("insert with columns inversion"){
        test_statement("CREATE TABLE a(c1 INT, c2 INT, c3 INT);"
                       "INSERT a(c2,c1) VALUES (12,14);"
                       "INSERT a(c3,c1,c2) VALUES (12,14,13);"
                       "SELECT * FROM a;",
                       "INSERT INTO a SUCCESSFUL.\n"
                       "|c1|c2|c3|\n"
                       "|12|14|12|\n"
                       "|14|13|  |");
    }

    SECTION("erase table before creation"){
        REQUIRE_THROWS(test_statement("CREATE TABLE a(c1 INT, c2 INT, column3 INT);"
                       "INSERT a(c1,c2,column3) VALUES (12,14,0);"
                       "INSERT a(c1,c2,column3) VALUES (1,1746,177);"
                       "SELECT c1,c2,c3 FROM a;",//c3 has to be undefined??
                       "SOME ERROR MESSAGE"));
    }

    SECTION("big insert"){
        roflan_parser::Driver parser_driver;
        std::string error_message;

        parser_driver.parse_string("create table test(id int, phone int);", error_message);
        parser_driver.sql_parser_result->execute();
        for (int i = 1; i < 20000; ++i) {
            auto k = i-1;
            parser_driver.parse_string("insert into test(id, phone) values (" + std::to_string(i) + ", " + std::to_string(k) + ");", error_message);
            parser_driver.sql_parser_result->execute();
        }
    }

    SECTION("big insert"){
        std::string single_insert = "INSERT a(c1,c2,c3) VALUES (1,2,3);";
        std::string single_select_output = "| 1| 2| 3|\n";
        test_statement("CREATE TABLE a(c1 INT, c2 INT, c3 INT);" +
                       repeat(1000,single_insert) + "SELECT * FROM a;",
                       "|c1|c2|c3|\n"+repeat(1000,single_select_output));
    }

    SECTION("negative ints"){
        test_statement("CREATE TABLE a(c1 INT, c2 INT);"
                       "INSERT INTO a(c2,c1) VALUES (-12,14);"
                       "SELECT c1,c2 FROM a;",
                       "INSERT INTO a SUCCESSFUL.\n"
                       "| c1|c2|\n"
                       "|-12|14|");
    }

}

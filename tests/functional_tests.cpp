#include <storage_engine_exceptions.h>
#include "catch.hpp"
#include "driver.h"
#include "storage_engine.h"
#include "inc/dtl/dtl.hpp"
#include "row_check.h"
#include "boost/filesystem.hpp"
#include <boost/asio.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/thread.hpp>
#include "boost/bind.hpp"
#include "boost/thread/thread.hpp"
#include <boost/chrono.hpp>
#include "iostream"
#include <future>

static std::string TEST_DELIMETER = "---";
static std::string TESTS_DIRECTORY = "tests";
static std::string TESTS_SUBDIRECTORY = "functional_tests";
static std::string MULTITHREAD_TESTS_SUBDIRECTORY = "multithread_tests";
static std::string PROJECT_DIRECTORY_NAME = "roflandb";

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
        parser_driver.parse_string("DROP TABLE a;DROP TABLE b;");
        parser_driver.sql_parser_result->execute();
    } catch(...){}
    parser_driver.parse_string(query, error_message);
    parser_driver.sql_parser_result->execute();
    std::string realoutput(parser_driver.sql_parser_result->get_messages());
    realoutput.erase(remove_if(realoutput.begin(), realoutput.end(), isspace), realoutput.end());
    //std::cout << "TEST OUTPUT " << output << std::endl;
    //std::cout << "REAL OUTPUT " << parser_driver.sql_parser_result->get_messages() << std::endl;
    //std::cout << "RESULT " << parser_driver.result << std::endl;
    try{
        parser_driver.parse_string("DROP TABLE a;DROP TABLE b;");
        parser_driver.sql_parser_result->execute();
    } catch(...){}
    return (compare(cleanoutput, realoutput));
}

std::string repeat(int n, std::string s) {
    std::ostringstream os;
    for (int i = 0; i < n; i++)
        os << s;
    return os.str();
}

boost::filesystem::path go_to_path(const std::string& dir, const std::string& subdir) {
    auto tests_path = boost::filesystem::current_path();
    while(tests_path.filename() != PROJECT_DIRECTORY_NAME){
        tests_path = tests_path.parent_path();
    }
    tests_path.append(dir).append(subdir);
    return tests_path;
}

TEST_CASE("All tests"){
    boost::filesystem::path tests_path = go_to_path(TESTS_DIRECTORY, TESTS_SUBDIRECTORY);
    for(auto& test_file: boost::filesystem::directory_iterator(tests_path)){
        std::cout << "RUNNING TEST " << test_file.path() << '\n';
        std::ifstream test(test_file.path().string());
        std::string mode;
        std::getline(test,mode);
        std::string t,query;
        while(std::getline(test,t)){
            if (t == TEST_DELIMETER){
                break;
            }
            query += t;
        }
        std::string result;
        while(std::getline(test,t)){
            result += t + "\n";
        }
        if (mode == "REQUIRE_FALSE"){
            REQUIRE_FALSE(test_statement(query,result));
        } else if (mode == "REQUIRE_THROWS"){
            REQUIRE_THROWS(test_statement(query,result));
        } else{
            REQUIRE(test_statement(query,result));
        }
    }
}
boost::asio::io_service service;

void parallel_execute_statement(std::string query, boost::chrono::high_resolution_clock::time_point *end, boost::asio::ip::tcp::endpoint& ep){
    using namespace boost::asio;
    ip::tcp::socket sock(service);

    streambuf b;
    //todo: send request
    sock.connect(ep);
    try {
        write(sock, buffer(query + '\0'));
        read_until(sock, b, '\0');
    }
    catch (boost::system::system_error &e) {
        std::cerr << e.what();
    }
    *end = boost::chrono::high_resolution_clock::now();
    sock.close();
}

TEST_CASE("parallel"){
    static std::string address = "127.0.0.1";
    static unsigned short port = 1337;
    boost::asio::ip::tcp::endpoint ep( boost::asio::ip::address::from_string(address), port);

    boost::filesystem::path tests_path = go_to_path(TESTS_DIRECTORY, MULTITHREAD_TESTS_SUBDIRECTORY);
    for(auto& test_file: boost::filesystem::directory_iterator(tests_path)) {
        std::vector <std::string> queries;
        std::vector <int> speeds; //the lower the speed, the longer the query has to execute, same speeds can be finished in any order
        std::ifstream test(test_file.path().string());
        std::string t;
        while(std::getline(test,t)){
            if (t == TEST_DELIMETER){
                std::getline(test,t);
                std::stringstream ss(t);
                for (int i = 0; i < queries.size(); ++i){
                    int tmp;
                    ss >> tmp;
                    speeds.push_back(tmp);
                }
                break;
            }
            queries.push_back(t);
        }

        using namespace boost::asio;
        boost::thread_group threads;
        boost::chrono::high_resolution_clock::time_point times[queries.size()];
        for (int i = 0; i < queries.size(); ++i) {
            threads.create_thread(boost::bind(parallel_execute_statement, queries[i], &times[i], ep));
            boost::this_thread::sleep( boost::posix_time::millisec(100));
        }
        threads.join_all();
        std::vector<std::pair<int,boost::chrono::high_resolution_clock::time_point>> queries_end_times(queries.size());
        for (int i = 0; i < queries.size(); ++i){
            queries_end_times[i].first = i;
            queries_end_times[i].second = times[i];
        }
        std::sort(queries_end_times.begin(),queries_end_times.end(), [](const std::pair<int,boost::chrono::high_resolution_clock::time_point> &x, const std::pair<int,boost::chrono::high_resolution_clock::time_point> &y){ return (x.second < y.second);});

        for (int j = 0; j < queries_end_times.size() - 1; ++j){
            REQUIRE_FALSE(speeds[queries_end_times[j].first] < speeds[queries_end_times[j+1].first]);
        }
    }

}

//TEST_CASE("insert not all columns","[.]"){
//    CHECK_THROWS(test_statement("CREATE TABLE a(c1 INT, c2 INT, c3 INT);"
//                              "INSERT a(c1,c2) VALUES (12,14);"
//                              "INSERT a(c1,c2,c3) VALUES (1,1746,177);"
//                              "SELECT c1,c2,c3 FROM a;"
//                              "DROP TABLE a;",
//                              "|c1|  c2| c3|\n"
//                              "|12|  14|177|\n"
//                              "| 1|1746|   |"));
//}
//
//TEST_CASE("select not all columns","[.]"){
//    CHECK_THROWS(test_statement("CREATE TABLE a(c1 INT, c2 INT, c3 INT);"
//                              "INSERT a(c1,c2) VALUES (12,14);"
//                              "INSERT a(c1,c2,c3) VALUES (1,1746,177);"
//                              "SELECT c1,c3 FROM a;"
//                              "DROP TABLE a;",
//                              "|c1| c3|\n"
//                              "|12|177|\n"
//                              "| 1|   |"));
//}
//

//TEST_CASE("insert with columns inversion","[.]"){
//    CHECK(test_statement("CREATE TABLE a(c1 INT, c2 INT, c3 INT);"
//                       "INSERT a(c2,c1) VALUES (12,14);"
//                       "INSERT a(c3,c1,c2) VALUES (12,14,13);"
//                       "SELECT * FROM a;"
//                       "DROP TABLE a;",
//                       "|c1|c2|c3|\n"
//                       "|12|14|12|\n"
//                       "|14|13|  |"));
//}
//
//std::string execute_query(const std::string &query) {
//    std::string error_message;
//    roflan_parser::Driver parser_driver;
//    parser_driver.parse_string(query, error_message);
//    parser_driver.sql_parser_result->execute();
//    return error_message;
//}
//
//TEST_CASE("Trivial testing of row_check","[.]"){
//    execute_query("CREATE TABLE a(c1 INT, c2 INT); INSERT INTO a(c1,c2) VALUES(1,2);");
//    std::vector<std::shared_ptr<st_e::TableCell>> cells;
//    cells.push_back(std::make_shared<st_e::IntegerTableCell>(st_e::IntegerTableCell(1)));
//    cells.push_back(std::make_shared<st_e::IntegerTableCell>(st_e::IntegerTableCell(2)));
//    st_e::TableRow row(cells, false);
//    auto cond = std::make_shared<cond::SimpleCondition>(cond::EQUAl,"c1","1");
//    REQUIRE(cond::row_check(st_e::StorageEngine::get_instance().get_table_by_name("a"), row, cond));
//}
//
//TEST_CASE("Trivial testing of row_check where condition is not true","[.]"){
//    execute_query("CREATE TABLE a(c1 INT, c2 INT); INSERT INTO a(c1,c2) VALUES(1,2);");
//    std::vector<std::shared_ptr<st_e::TableCell>> cells;
//    cells.push_back(std::make_shared<st_e::IntegerTableCell>(st_e::IntegerTableCell(1)));
//    cells.push_back(std::make_shared<st_e::IntegerTableCell>(st_e::IntegerTableCell(2)));
//    st_e::TableRow row(cells, false);
//    auto cond = std::make_shared<cond::SimpleCondition>(cond::EQUAl,"c1","123");
//    REQUIRE_FALSE(cond::row_check(st_e::StorageEngine::get_instance().get_table_by_name("a"), row, cond));
//}
//
//TEST_CASE("LESS condition","[.]"){
//    execute_query("CREATE TABLE a(c1 INT, c2 INT); INSERT INTO a(c1,c2) VALUES(1,2,3);");
//    std::vector<std::shared_ptr<st_e::TableCell>> cells;
//    cells.push_back(std::make_shared<st_e::IntegerTableCell>(st_e::IntegerTableCell(1)));
//    cells.push_back(std::make_shared<st_e::IntegerTableCell>(st_e::IntegerTableCell(2)));
//    st_e::TableRow row(cells, false);
//    auto cond = std::make_shared<cond::SimpleCondition>(cond::LESS,"c2","123");
//    REQUIRE(cond::row_check(st_e::StorageEngine::get_instance().get_table_by_name("a"), row, cond));
//}
//
//TEST_CASE("LESS_EQUAL condition","[.]"){
//    execute_query("CREATE TABLE a(c1 INT, c2 INT); INSERT INTO a(c1,c2) VALUES(1,2,3);");
//    std::vector<std::shared_ptr<st_e::TableCell>> cells;
//    cells.push_back(std::make_shared<st_e::IntegerTableCell>(st_e::IntegerTableCell(1)));
//    cells.push_back(std::make_shared<st_e::IntegerTableCell>(st_e::IntegerTableCell(2)));
//    st_e::TableRow row(cells, false);
//    auto cond = std::make_shared<cond::SimpleCondition>(cond::LESS_EQUAL,"c2","2");
//    REQUIRE(cond::row_check(st_e::StorageEngine::get_instance().get_table_by_name("a"), row, cond));
//}
//
//TEST_CASE("GREATER condition","[.]"){
//    execute_query("CREATE TABLE a(c1 INT, c2 INT); INSERT INTO a(c1,c2) VALUES(1,2,3);");
//    std::vector<std::shared_ptr<st_e::TableCell>> cells;
//    cells.push_back(std::make_shared<st_e::IntegerTableCell>(st_e::IntegerTableCell(1)));
//    cells.push_back(std::make_shared<st_e::IntegerTableCell>(st_e::IntegerTableCell(2)));
//    st_e::TableRow row(cells, false);
//    auto cond = std::make_shared<cond::SimpleCondition>(cond::GREATER,"c2","0");
//    REQUIRE(cond::row_check(st_e::StorageEngine::get_instance().get_table_by_name("a"), row, cond));
//}
//
//TEST_CASE("GREATER_OR_EQUAL condition","[.]"){
//    execute_query("CREATE TABLE a(c1 INT, c2 INT); INSERT INTO a(c1,c2) VALUES(1,2,3);");
//    std::vector<std::shared_ptr<st_e::TableCell>> cells;
//    cells.push_back(std::make_shared<st_e::IntegerTableCell>(st_e::IntegerTableCell(1)));
//    cells.push_back(std::make_shared<st_e::IntegerTableCell>(st_e::IntegerTableCell(2)));
//    st_e::TableRow row(cells, false);
//    auto cond = std::make_shared<cond::SimpleCondition>(cond::GREATER_EQUALS,"c2","2");
//    REQUIRE(cond::row_check(st_e::StorageEngine::get_instance().get_table_by_name("a"), row, cond));
//}
//
//TEST_CASE("Integers less than 0","[.]"){
//    execute_query("CREATE TABLE a(c1 INT, c2 INT); INSERT INTO a(c1,c2) VALUES(-1,-2,-3);");
//    std::vector<std::shared_ptr<st_e::TableCell>> cells;
//    cells.push_back(std::make_shared<st_e::IntegerTableCell>(st_e::IntegerTableCell(1)));
//    cells.push_back(std::make_shared<st_e::IntegerTableCell>(st_e::IntegerTableCell(2)));
//    st_e::TableRow row(cells, false);
//    auto cond = std::make_shared<cond::SimpleCondition>(cond::LESS,"c2","123");
//    REQUIRE(cond::row_check(st_e::StorageEngine::get_instance().get_table_by_name("a"), row, cond));
//}

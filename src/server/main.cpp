#include "main.h"
#include "driver.h"

int main() {
    std::cout << "Hello, world!" << std::endl;
    std::cout << "My name is RoflanDB." << std::endl;
    std::cout << "RoflanDB strong!" << std::endl;

    RoflanParser::Driver driver;
    std::string answer;
//    driver.parse_string("create", answer);
//    std::cout << driver.result;

    while (true) {
        std::string sql_query;
        std::cout << "Enter query \n";

        std::getline(std::cin, sql_query);
        driver.parse_string(sql_query, answer);
        std::cout << driver.result << "\n";
//        std::cout << command << " SQL \n";
    }



    return 0;
}

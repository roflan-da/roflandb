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
        std::string command;
        std::cout << "Enter query \n";

        std::getline(std::cin, command);
        driver.parse_string(command, answer);
        std::cout << driver.result;
//        std::cout << command << " SQL \n";
    }



    return 0;
}

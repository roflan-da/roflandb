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
        if ((command.length() >= 2) && (command[0] == '\\')){
            switch (command[1]){
                case 'q':{
                    //save work
                }
                case 'e':{
                    std::cout << "Exiting" << std::endl;
                    return 0;
                }
                case ('?'):
                case ('h'):{
                    std::cout << "There will be help!" << std::endl;
                }
            }
        } else{
            try{
                driver.parse_string(command, answer);
                std::cout << driver.result;
            } catch (std::exception& e){
                std::cout << "Unknown error!";
            }
        }
//        std::cout << command << " SQL \n";
    }



    return 0;
}

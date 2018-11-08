#include "main.h"
#include "driver.h"
#include "storage_engine.h"


int main() {
    std::cout << "Hello, world!" << std::endl;
    std::cout << "My name is RoflanDB." << std::endl;
    std::cout << "RoflanDB strong!" << std::endl;

    RoflanParser::Driver parserDriver;
    std::string answer;
    st_e::StorageEngine storageEngine;

//    parserDriver.parse_string("create", answer);
//    std::cout << parserDriver.result;
//    auto condOR = cond::Condition();       by mup0c 08.11

    while (true) {
        std::string sql_query;
        std::cout << "Enter query \n";

        std::getline(std::cin, sql_query);
        if ((sql_query.length() >= 2) && (sql_query[0] == '\\')){
            switch (sql_query[1]){
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
                default:break;
            }
        } else{
            try{
                parserDriver.parse_string(sql_query, answer);
                parserDriver.SQLParseResult->execute(storageEngine);
                std::cout << parserDriver.result;
            } catch (std::exception& e){
                std::cout << "Unknown error!";
            }
        }
//        std::cout << sql_query << " SQL \n";
    }



    return 0;
}

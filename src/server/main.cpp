#include "main.h"
#include "driver.h"
#include "storage_engine.h"
class CLITexts
{
public:
    static CLITexts& Instance()
    {
        // согласно стандарту, этот код ленивый и потокобезопасный
        static CLITexts s;
        return s;
    }

    std::string get_gelp(){
        return "RoflanDB: a database better then mariadb\n"
               "(C) 2018 by Roflan Digital Agency\n"
               "COMMANDS\n"
               "\\q - save work\n"
               "\\e - exit CLI\n"
               "\\?, \\h - show this help\n";
    }

private:
    CLITexts() {}  // конструктор недоступен
    ~CLITexts() {} // и деструктор

    // необходимо также запретить копирование
    CLITexts(CLITexts const&); // реализация не нужна
    CLITexts& operator= (CLITexts const&);  // и тут
};

int main() {
    CLITexts& cli_texts = CLITexts::Instance();

    std::cout << "RoflanDB command line" << std::endl;
    std::cout << "Enter \\h for help" << std::endl;

    RoflanParser::Driver parserDriver;
    std::string answer;
    st_e::StorageEngine storageEngine;

//    parserDriver.parse_string("create", answer);
//    std::cout << parserDriver.result;
//    auto condOR = cond::Condition();       by mup0c 08.11

    while (true) {
        std::string sql_query;
        std::cout << "Enter query: \n";
        std::getline(std::cin, sql_query);
        if ((sql_query.length() >= 2) && (sql_query[0] == '\\')){
            switch (sql_query[1]){
                case 'q':{
                    //save work
                    st_e::StorageEngine e;
                    e.save();
                }
                case 'e':{
                    std::cout << "Exiting" << std::endl;
                    return 0;
                }
                case ('?'):
                case ('h'):{
                    std::cout << cli_texts.get_gelp();
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

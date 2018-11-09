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
               "\\?, \\h - show this help\n"
               "\\a - show authors\n";
    }

    std::string get_authors(){
        return "RoflanDB is proudly brought to you by:\n"
               "-Alexey Mogilevkin\n"
               "-Artyom Sityaev\n"
               "-Sergey Zinkovich\n"
               "-Boris Timofeenko\n"
               "Miroslav Koberskij\n";
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
    std::cout << " ____  _____  ____  __      __    _  _  ____   ____" << std::endl;
    std::cout << "(  _ \\(  _  )( ___)(  )    /__\\  ( \\( )(  _ \\ (  _ \\" << std::endl;
    std::cout << " )   / )(_)(  )__)  )(__  /(__)\\  )  (  )(_) ) ) _ <" << std::endl;
    std::cout << "(_)\\_)(_____)(__)  (____)(__)(__)(_)\\_)(____/ (____/" << std::endl;
    std::cout << "RoflanDB command line" << std::endl;
    std::cout << "Enter \\h for help" << std::endl;

    roflan_parser::Driver parserDriver;
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
                    return 0;
                }
                case 'e':{
                    std::cout << "Exiting" << std::endl;
                    return 0;
                }
                case ('?'):
                case ('h'):{
                    std::cout << cli_texts.get_gelp();
                }
                case ('a'):{
                    std::cout << cli_texts.get_authors();
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

#include "main.h"
#include "storage_engine.h"
#include <fstream>
#include <storage_engine.h>

int main() {
    std::cout << "Hello, world!" << std::endl;
    std::cout << "My name is RoflanDB." << std::endl;
    std::cout << "RoflanDB strong!" << std::endl;
    /*//чтение
    std::ifstream in("My_db.txt");
    //std::string tables_string;
    st_e::StorageEngine storageEngine;
    //in >> tables_string;

    std::string command;
    while (true) {
        std::cin >> command;
        std::cout << command;
    }


    return 0;
}

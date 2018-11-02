#include "main.h"
#include "storage_engine.h"
#include <fstream>
#include <storage_engine.h>

int main() {
    std::cout << "Hello, world!" << std::endl;
    std::cout << "My name is RoflanDB." << std::endl;
    std::cout << "RoflanDB strong!" << std::endl;

    std::string command;
    while (true) {
        std::cin >> command;
        std::cout << command;
    }


    return 0;
}

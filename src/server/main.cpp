#include "main.h"

int main() {
    std::cout << "Hello, world!" << std::endl;
    std::cout << "My name is RoflanDB." << std::endl;
    std::cout << "RoflanDB strong!" << std::endl;

    while (true) {
        std::string command;
        std::cout << "Enter query without \\n: \n";

        std::getline(std::cin, command);
        std::cout << command << " SQL \n";
    }



    return 0;
}

#include "main.h"
#include "table.h"

int main() {
    std::cout << "Hello, world!" << std::endl;
    std::cout << "My name is RoflanDB." << std::endl;
    std::cout << "RoflanDB strong!" << std::endl;
    TableBuilder tableBuilder("Kektable");
    tableBuilder.addColumn("INT", "kekcolumn");
    Table table = tableBuilder.build();
    std::cout << table.getSql();
    return 1;
}

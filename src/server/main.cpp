#include "main.h"
#include "storage_engine.h"
#include <fstream>
#include <storage_engine.h>

int main() {
    std::cout << "Hello, world!" << std::endl;
    std::cout << "My name is RoflanDB." << std::endl;
    std::cout << "RoflanDB strong!" << std::endl;
    //чтение
    std::ifstream in("My_db.txt");
    //std::string tables_string;
    st_e::StorageEngine storageEngine;
    //in >> tables_string;

    storageEngine.Load(in);
    //запись
    st_e::StorageEngine tableStorage;
    TableBuilder tableBuilder1("kektable");
    tableBuilder1.addColumn("INT", "kekcolumn1");
    tableBuilder1.addColumn("INT", "kekcolumn2");
    tableBuilder1.addColumn("INT", "kekcolumn3");
    TableBuilder tableBuilder2("kektable2");
    tableBuilder2.addColumn("INT", "kekcolumn1");
    tableBuilder2.addColumn("INT", "kekcolumn2");
    tableBuilder2.addColumn("INT", "kekcolumn3");
    Table table1 = tableBuilder1.build();
    Table table2 = tableBuilder2.build();
    tableStorage.addTable(std::make_shared<Table>(table1));
    tableStorage.addTable(std::make_shared<Table>(table2));
    std::ofstream out("My_db.txt");
    out << storageEngine.Save();
    return 1;
}

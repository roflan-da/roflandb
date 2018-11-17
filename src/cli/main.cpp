#include "cli.h"
#include "shared_table.h"

int main(int argc, char *argv[]) {
    auto& sharedTable = st_e::SharedTable::get_instance();

//    std::vector<st_e::Column> columns = {st_e::Column(st_e::Column::Type::INT, "id"), st_e::Column(st_e::Column::Type::INT, "NUMBER")};
//    st_e::Table t("sample table", columns);
//    sharedTable.save_table(t);
    auto t = sharedTable.get_table("sample table");
//    int a = 2;
//    auto& cli = roflan_cli::Cli::get_instance();
//    return cli.start();
}

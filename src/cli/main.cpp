#include "cli.h"
#include "shared_table.h"

int main(int argc, char *argv[]) {
    auto& sharedTable = st_e::SharedTable::get_instance();
    sharedTable.get_table("mem");
//    auto& cli = roflan_cli::Cli::get_instance();
//    return cli.start();
}

#include "cli.h"
#include "shared_table.h"

int main(int argc, char *argv[]) {
    auto& cli = roflan_cli::Cli::get_instance();
    return cli.start();
}

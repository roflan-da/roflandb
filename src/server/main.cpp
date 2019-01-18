#include "server.h"
#include "shared_table.h"

int main(int argc, char *argv[]) {
    auto& cli = roflan_srv::Server::get_instance();
    return cli.start();
}

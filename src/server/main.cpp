#include "server.h"
#include "shared_table.h"

int main(int argc, char *argv[]) {
    auto& srv = roflan_srv::Server::get_instance();
    return srv.start();
}

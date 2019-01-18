#include <iostream>
#include "driver.h"
#include "storage_engine.h"
#include <server.h>
#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;

namespace roflan_srv {

Server& Server::get_instance() {
    static Server instance;
    return instance;
}

int Server::start() {
    roflan_parser::Driver parser_driver;
    int thread_count = 4;

    try {
        TcpServer server(io_service_);
        signal_set sig(io_service_, SIGINT, SIGTERM);
        sig.async_wait(std::bind(&Server::signal_handler, this, std::placeholders::_1, std::placeholders::_2));

        for (int i = 0; i < thread_count; i++) {
            threads_.create_thread(boost::bind(&Server::listen_thread, this));
        }

        threads_.join_all();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}

void Server::listen_thread() {
    io_service_.run();
}

bool Server::is_starts_with(const std::string& hay, const std::string& needle) const {
    return hay.compare(0, needle.length(), needle) == 0;
}

void Server::signal_handler(const boost::system::error_code&, int signal) {
    std::cout << "exiting...";
    io_service_.stop();
}

} // namespace roflan_srv
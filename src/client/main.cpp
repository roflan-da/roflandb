#include <iostream>
#include "server.h"
#include "driver.h"
#include "storage_engine.h"
#include "server.h"
#include "texts.h"

#include <boost/asio.hpp>

namespace roflan_cli {

Server& Server::get_instance() {
    static Server instance;
    return instance;
}

int Server::start() {
    // init section
    std::istream& input = std::cin;
    std::ostream& output = std::cout;
    std::ostream& error = std::cerr;

    Texts::print_startup_message(output);

    roflan_parser::Driver parser_driver;
    std::string query;
    std::string error_message;

    // main loop
    while (true) {
        // print prompt
        output << "rdb> ";

        std::getline(input, query);
        // Handle not sql commands
        if (is_starts_with(query, "\\q")) {
            // Todo: implement
            // storage_engine.on_shutdown()
            return EXIT_SUCCESS;
        } else if (is_starts_with(query, "\\a")) {
            Texts::print_authors(output);
            continue;
        } else if (is_starts_with(query, "\\?") || is_starts_with(query, "\\h")) {
            Texts::print_help(output);
            continue;
        }

        if (!parser_driver.parse_string(query, error_message)) {
            error << error_message << std::endl;
            continue;
        }
        parser_driver.sql_parser_result->execute();
        output << parser_driver.sql_parser_result->get_messages();
        output << parser_driver.result;
    }
    return EXIT_SUCCESS;
}

bool Server::is_starts_with(const std::string& hay, const std::string& needle) const {
    return hay.compare(0, needle.length(), needle) == 0;
}

} // namespace roflan_cli
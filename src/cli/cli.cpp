#include <iostream>
#include "cli.h"
#include "driver.h"
#include "storage_engine.h"
#include "cli.h"
#include "cli_texts.h"

roflan_cli::Cli& roflan_cli::Cli::get_instance() {
    static Cli instance;
    return instance;
}

int roflan_cli::Cli::start() {
    // init section
    std::istream& input = std::cin;
    std::ostream& output = std::cout;
    std::ostream& error = std::cerr;

    CliTexts::print_startup_message(output);

    roflan_parser::Driver parser_driver;
    st_e::StorageEngine storage_engine;
    std::string query;
    std::string error_message;

    // main loop
    while (true) {
        //print prompt
        output << "rdb> ";

        std::getline(input, query);
        // Handle not sql commands
        if (is_starts_with(query, "\\q")) {
            // Todo: implement
            // storage_engine.on_shutdown()
            return EXIT_SUCCESS;
        } else if (is_starts_with(query, "\\a")) {
            CliTexts::print_authors(output);
            continue;
        } else if (is_starts_with(query, "\\?") || is_starts_with(query, "\\h")) {
            CliTexts::print_help(output);
            continue;
        }

        if (!parser_driver.parse_string(query, error_message)) {
            error << error_message << std::endl;
            continue;
        }
        parser_driver.sql_parser_result->execute(storage_engine);
        output << parser_driver.result;
    }
    return EXIT_SUCCESS;
}

bool roflan_cli::Cli::is_starts_with(const std::string& hay, const std::string& needle) const {
    return hay.compare(0, needle.length(), needle) == 0;
}

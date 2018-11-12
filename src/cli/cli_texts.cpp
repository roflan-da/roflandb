#include "cli_texts.h"

namespace roflan_cli {

void roflan_cli::CliTexts::print_help(std::ostream& output_steam) {
    output_steam << "RoflanDB: a database better then mariadb" << std::endl;
    output_steam << "(C) 2018 by Roflan Digital Agency"        << std::endl;
    output_steam                                               << std::endl;
    output_steam << "COMMANDS"                                 << std::endl;
    output_steam                                               << std::endl;
    output_steam << "\\q - exit CLI"                           << std::endl;
    output_steam << "\\?, \\h - show this message"             << std::endl;
    output_steam << "\\a authors"                              << std::endl;
}

void roflan_cli::CliTexts::print_authors(std::ostream& output_steam) {
    output_steam << "RoflanDB is proudly brought to you by:" << std::endl;
    output_steam << "- Alexey Mogilyovkin"                   << std::endl;
    output_steam << "- Artem Sityaev"                        << std::endl;
    output_steam << "- Sergey Zinkovich"                     << std::endl;
    output_steam << "- Boris Timofeenko"                     << std::endl;
    output_steam << "- Miroslav Koberskiy"                   << std::endl;
}

void roflan_cli::CliTexts::print_startup_message(std::ostream& output_stream) {
    std::cout <<  " ____  _____  ____  __      __    _  _  ____   ____"    << std::endl;
    std::cout << R"((  _ \(  _  )( ___)(  )    /__\  ( \( )(  _ \ (  _ \)" << std::endl;
    std::cout << R"( )   / )(_)(  )__)  )(__  /(__)\  )  (  )(_) ) ) _ <)" << std::endl;
    std::cout << R"((_)\_)(_____)(__)  (____)(__)(__)(_)\_)(____/ (____/)" << std::endl;
    std::cout << "RoflanDB command line"                                   << std::endl;
    std::cout << "Enter \\h for help"                                      << std::endl;
}

} // roflan_cli

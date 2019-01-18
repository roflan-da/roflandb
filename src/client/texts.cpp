#include "texts.h"

namespace roflan_cli {

void Texts::print_help(std::ostream& output_steam) {
    output_steam << "RoflanDB: a database better then mariadb" << std::endl;
    output_steam << "(C) 2018 by Roflan Digital Agency"        << std::endl;
    output_steam                                               << std::endl;
    output_steam << "COMMANDS"                                 << std::endl;
    output_steam                                               << std::endl;
    output_steam << "\\q - exit CLI"                           << std::endl;
    output_steam << "\\?, \\h - show this message"             << std::endl;
    output_steam << "\\a authors"                              << std::endl;
}

void Texts::print_authors(std::ostream& output_steam) {
    output_steam << "RoflanDB is proudly brought to you by:" << std::endl;
    output_steam << "- Alexey Mogilyovkin"                   << std::endl;
    output_steam << "- Artem Sityaev"                        << std::endl;
    output_steam << "- Sergey Zinkovich"                     << std::endl;
    output_steam << "- Boris Timofeenko"                     << std::endl;
    output_steam << "- Miroslav Koberskiy"                   << std::endl;
}

void Texts::print_startup_message(std::ostream& output_stream) {
    output_stream <<  " ____  _____  ____  __      __    _  _  ____   ____"    << std::endl;
    output_stream << R"((  _ \(  _  )( ___)(  )    /__\  ( \( )(  _ \ (  _ \)" << std::endl;
    output_stream << R"( )   / )(_)(  )__)  )(__  /(__)\  )  (  )(_) ) ) _ <)" << std::endl;
    output_stream << R"((_)\_)(_____)(__)  (____)(__)(__)(_)\_)(____/ (____/)" << std::endl;
    output_stream << "RoflanDB command line"                                   << std::endl;
    output_stream << "Enter \\h for help"                                      << std::endl;
}

void Texts::print_goodbye_message(std::ostream& output_stream) {
    output_stream << "Bye, bye...";
}

} // roflan_srv

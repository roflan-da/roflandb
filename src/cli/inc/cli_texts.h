#pragma once

#include <string>
#include <iostream>

namespace roflan_cli {

class CliTexts {
public:
    CliTexts() = delete;
    CliTexts(CliTexts const&) = delete;
    CliTexts& operator=(CliTexts const&) = delete;

    static void print_help(std::ostream& output_steam);
    static void print_authors(std::ostream& output_steam);
    static void print_startup_message(std::ostream& output_stream);
};

} // namespace roflan_cli

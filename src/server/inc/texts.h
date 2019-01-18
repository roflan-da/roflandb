#pragma once

#include <string>
#include <iostream>

namespace roflan_srv {

class Texts {
public:
    Texts() = delete;
    Texts(Texts const&) = delete;
    Texts& operator=(Texts const&) = delete;

    static void print_help(std::ostream& output_steam);
    static void print_authors(std::ostream& output_steam);
    static void print_startup_message(std::ostream& output_stream);
};

} // namespace roflan_srv

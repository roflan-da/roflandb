#include <iostream>
#include <texts.h>

#include <boost/asio.hpp>
#include <boost/asio/read_until.hpp>

using namespace roflan_cli;
using namespace boost::asio;

bool is_starts_with(const std::string& hay, const std::string& needle)  {
    return hay.compare(0, needle.length(), needle) == 0;
}

int main(int argc, char *argv[]) {
    std::istream& input = std::cin;
    std::ostream& output = std::cout;
    std::ostream& error = std::cerr;

    io_service io_service;
    ip::tcp::endpoint ep(ip::address_v4::loopback(), 1337);

    std::string answer;

    Texts::print_startup_message(output);
    std::string query;

    while (true) {
        // print prompt
        output << "rdb> ";

        std::getline(input, query);
        // Handle not sql commands
        if (is_starts_with(query, "\\q")) {
            Texts::print_goodbye_message(output);
            return EXIT_SUCCESS;
        } else if (is_starts_with(query, "\\a")) {
            Texts::print_authors(output);
            continue;
        } else if (is_starts_with(query, "\\?") || is_starts_with(query, "\\h")) {
            Texts::print_help(output);
            continue;
        }

        ip::tcp::socket sock(io_service);
        streambuf b;
        //todo: send request
        sock.connect(ep);
        try {
            write(sock, buffer(query + '\0'));
            read_until(sock, b, '\0');
        }
        catch (boost::system::system_error &e) {
            std::cerr << e.what();
        }

        std::istream is(&b);
        std::getline(is, answer);
        std::cout << answer << std::endl;

    }
}


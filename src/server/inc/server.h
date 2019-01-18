#pragma once

#include <string>
#include <tcp_server.h>

namespace roflan_srv {

// Meyers singleton. Thread unsafe.
class Server
{
public:
    Server( const Server&) = delete;
    Server& operator=(Server&) = delete;

    static Server& get_instance();

    // return exit code;
    int start();
    void signal_handler(const boost::system::error_code&, int signal);
private:
    Server() = default;
    boost::asio::io_service io_service_;
    bool is_starts_with(const std::string& hay, const std::string& needle) const;

};

} // namespace roflan_srv

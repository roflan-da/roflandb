#pragma once

#include <string>
#include <tcp_server.h>
#include <boost/thread.hpp>

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
    void listen_thread();
private:
    Server() = default;
    boost::asio::io_context io_service_;
    bool is_starts_with(const std::string& hay, const std::string& needle) const;
    boost::thread_group threads_;

};

} // namespace roflan_srv

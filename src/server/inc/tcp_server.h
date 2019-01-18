#pragma once

#include <boost/asio.hpp>
#include <tcp_connection.h>
#include <driver.h>

namespace roflan_srv {

class TcpServer {
public:
    explicit TcpServer(boost::asio::io_service& io_service);

    void start_accept();
    void handle_accept(TcpConnection::pointer new_connection, const boost::system::error_code& error);

private:
    boost::asio::ip::tcp::acceptor acceptor_;
};

} //namespace roflan_srv
#include <tcp_server.h>
#include <boost/bind.hpp>

using namespace boost::asio;

namespace roflan_srv {

TcpServer::TcpServer(boost::asio::io_service &io_service)
        : acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 1337))
{
    start_accept();
}

void roflan_srv::TcpServer::start_accept() {
    TcpConnection::pointer new_connection = TcpConnection::create(acceptor_.get_io_service());

    acceptor_.async_accept(new_connection->socket(),
                           boost::bind(&TcpServer::handle_accept, this, new_connection, placeholders::error));
}

void TcpServer::handle_accept(TcpConnection::pointer new_connection, const boost::system::error_code& error) {
    if (!error) {
        new_connection->start();
    }

    start_accept();
}

} // roflan_srv
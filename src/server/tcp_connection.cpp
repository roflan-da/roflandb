#include <tcp_connection.h>
#include <boost/bind.hpp>

using namespace boost::asio;

namespace roflan_srv {

boost::asio::ip::tcp::socket& TcpConnection::socket() {
    return socket_;
}

void TcpConnection::start() {
    message_ = "sdadsdaasdssheh";
    boost::asio::async_write(socket_, boost::asio::buffer(message_),
                             boost::bind(&TcpConnection::handle_write, shared_from_this(),
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}

TcpConnection::TcpConnection(boost::asio::io_service& io_service) : socket_(io_service) {

}

void TcpConnection::handle_write(const boost::system::error_code&, size_t) {

}

void TcpConnection::handle_write() {

}

} //namespace roflan_srv
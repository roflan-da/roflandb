#include <tcp_connection.h>
#include <boost/bind.hpp>
#include <iostream>

using namespace boost::asio;

namespace roflan_srv {

boost::asio::ip::tcp::socket& TcpConnection::socket() {
    return socket_;
}

void TcpConnection::start() {
    std::cout << "start" << std::endl;

    async_read_until(socket_ , query_, '\0',
            boost::bind(
                    &TcpConnection::handle_read, shared_from_this(), placeholders::error, placeholders::bytes_transferred()));

//    boost::asio::async_write(socket_, boost::asio::buffer(message_),
//                             boost::bind(&TcpConnection::handle_write, shared_from_this(),
//                                         boost::asio::placeholders::error,
//                                         boost::asio::placeholders::bytes_transferred));
}

TcpConnection::TcpConnection(boost::asio::io_service& io_service) : socket_(io_service) {
}

void TcpConnection::handle_write(const boost::system::error_code&, size_t) {
//    std::cout << "handle write" << std::endl << query_ << std::endl;
}

void TcpConnection::handle_read(const boost::system::error_code&, size_t) {
//    std::cout << "handle read" << std::endl << query_ << std::endl;
    async_write(socket_, query_,
                boost::bind(&TcpConnection::handle_write, shared_from_this(), boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));

}

} //namespace roflan_srv
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

}

TcpConnection::TcpConnection(boost::asio::io_service& io_service) : socket_(io_service) {
}

void TcpConnection::handle_write(const boost::system::error_code&, size_t) {
}

void TcpConnection::handle_read(const boost::system::error_code&, size_t) {
    std::string error_message;
    streambuf::const_buffers_type bufs = query_.data();
    std::string query(boost::asio::buffers_begin(bufs),
                    boost::asio::buffers_begin(bufs) + bufs.size());

    parser_driver_.parse_string(query, error_message);

    if (!parser_driver_.parse_string(query, error_message)) {
        async_write(socket_, buffer(error_message + '\0'),
                    boost::bind(&TcpConnection::handle_write, shared_from_this(), boost::asio::placeholders::error,
                                boost::asio::placeholders::bytes_transferred));
        return;
    }
        parser_driver_.sql_parser_result->execute();
//        output << parser_driver_.sql_parser_result->get_messages();
//        output << parser_driver_.result;

    auto kek = parser_driver_.sql_parser_result->get_messages();

    async_write(socket_, buffer(parser_driver_.sql_parser_result->get_messages() + '\0'),
                boost::bind(&TcpConnection::handle_write, shared_from_this(), boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));

}

} //namespace roflan_srv
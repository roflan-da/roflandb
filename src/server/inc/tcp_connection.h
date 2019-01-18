#pragma once

#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

namespace roflan_srv {

class TcpConnection : public boost::enable_shared_from_this<TcpConnection> {
public:
    typedef boost::shared_ptr<TcpConnection> pointer;

    explicit TcpConnection(boost::asio::io_service& io_service);

    static pointer create(boost::asio::io_service& io_service) {
        return pointer(new TcpConnection(io_service));
    }

    boost::asio::ip::tcp::socket& socket();

    void start();
    void handle_write(const boost::system::error_code& , size_t /*bytes_transferred*/);
    void handle_write();

private:
    boost::asio::ip::tcp::socket socket_;
    std::string message_;
};

}
// //namespace roflan_srv

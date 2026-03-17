#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <memory>

using boost::asio::ip::tcp;

class Server {
public:
    Server(boost::asio::io_context& io_context, unsigned short port);
    void start_accept();

private:
    void handle_accept(std::shared_ptr<tcp::socket> socket,
                       const boost::system::error_code& error);

    boost::asio::io_context& io_context_;
    tcp::acceptor acceptor_;
};

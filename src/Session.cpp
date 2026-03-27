#include "Session.h"
#include <iostream>
#include <algorithm>

Session::Session(std::shared_ptr<tcp::socket> socket)
    : socket_(std::move(socket))
{
}

void Session::start()
{
    do_read();
    do_write("Welcome to MUD-Space!\r\n> ");
}

void Session::do_read()
{
    auto self = shared_from_this();
    socket_->async_read_some(
        boost::asio::buffer(read_buffer_),
        [this, self](const boost::system::error_code& ec, std::size_t length) {
            if (!ec) {
                std::string input(read_buffer_, length);
                std::cout << "Received: " << input << std::endl;

                // Echo back the input
                do_write("You typed: " + input + "\r\n> ");
                do_read(); // Continue reading
            } else {
                std::cerr << "Client disconnected: " << ec.message() << std::endl;
            }
        });
}

void Session::do_write(const std::string& msg)
{
    auto self = shared_from_this();
    boost::asio::async_write(
        *socket_,
        boost::asio::buffer(msg),
        [this, self](boost::system::error_code ec, std::size_t /*length*/) {
            if (ec) {
                std::cerr << "Write error: " << ec.message() << std::endl;
            }
        });
}

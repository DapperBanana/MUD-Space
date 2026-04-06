#include "Session.h"
#include <iostream>

Session::Session(std::shared_ptr<tcp::socket> socket)
    : socket_(std::move(socket))
{
}

void Session::start()
{
    do_write("Welcome to MUD-Space!\r\n> ");
    do_read();
}

void Session::disconnect()
{
    disconnecting_ = true;
}

void Session::do_read()
{
    auto self = shared_from_this();
    socket_->async_read_some(
        boost::asio::buffer(read_buffer_),
        [this, self](const boost::system::error_code& ec, std::size_t length) {
            if (ec) {
                std::cout << "Client disconnected" << std::endl;
                return;
            }
            std::string raw_input(read_buffer_, length);
            std::string response = command_dispatcher_.dispatch(*this, raw_input);
            do_write(response);
            if (!disconnecting_)
            {
                do_write("> ");
                do_read();
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
                std::cout << "Client disconnected during write" << std::endl;
                return;
            }
        });
}

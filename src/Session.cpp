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

            std::string input(read_buffer_, length);
            ParsedCommand cmd = parser_.parse(input);
            std::string response = dispatcher_.dispatch(*this, cmd);

            if (disconnecting_) {
                do_write(response);
                return;
            }

            if (!response.empty()) {
                do_write(response + "> ");
            } else {
                do_write("> ");
            }

            do_read();
        });
}

void Session::do_write(const std::string& msg)
{
    auto self = shared_from_this();
    auto buf = std::make_shared<std::string>(msg);
    boost::asio::async_write(*socket_,
        boost::asio::buffer(*buf),
        [this, self, buf](const boost::system::error_code& ec, std::size_t /*length*/) {
            if (ec) {
                std::cout << "Write error: " << ec.message() << std::endl;
                return;
            }
            if (disconnecting_) {
                boost::system::error_code close_ec;
                socket_->close(close_ec);
            }
        });
}

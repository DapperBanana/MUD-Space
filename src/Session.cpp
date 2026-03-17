#include "Session.h"
#include <iostream>
#include <algorithm>

Session::Session(std::shared_ptr<tcp::socket> socket)
    : socket_(std::move(socket))
{
}

void Session::start()
{
    do_write("Welcome to MUD-Space!\r\n> ");
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

            std::string input(read_buffer_.data(), length);
            // strip trailing \r\n from telnet
            input.erase(std::remove(input.begin(), input.end(), '\r'), input.end());
            input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());

            if (!input.empty()) {
                process_input(input);
            } else {
                do_write("> ");
            }
        });
}

void Session::do_write(const std::string& msg)
{
    auto self = shared_from_this();
    boost::asio::async_write(*socket_,
        boost::asio::buffer(msg),
        [this, self](const boost::system::error_code& ec, std::size_t) {
            if (!ec) {
                do_read();
            }
        });
}

void Session::process_input(const std::string& input)
{
    if (input == "quit" || input == "exit") {
        do_write("Goodbye, spacer.\r\n");
        socket_->close();
        return;
    }

    if (input == "look") {
        do_write("You float in the void of space. Stars glimmer in every direction.\r\n> ");
        return;
    }

    do_write("Unknown command: " + input + "\r\n> ");
}

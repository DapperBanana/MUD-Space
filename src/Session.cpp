#include "Session.h"
#include "CommandParser.h"
#include <iostream>
#include <algorithm>
#include <sstream>

Session::Session(std::shared_ptr<tcp::socket> socket)
    : socket_(std::move(socket))
{
}

void Session::start()
{
    do_write("Welcome to MUD-Space!\r\n> ");
    do_read();
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
            handle_input(input);
            do_read();
        });
}

void Session::handle_input(const std::string& input)
{
    ParsedCommand cmd = CommandParser::parse(input);

    if (cmd.empty()) {
        do_write("> ");
        return;
    }

    if (cmd.verb == "quit" || cmd.verb == "exit") {
        do_write("Goodbye!\r\n");
        socket_->close();
        return;
    }

    if (cmd.verb == "say" && !cmd.args.empty()) {
        std::string message;
        for (size_t i = 0; i < cmd.args.size(); ++i) {
            if (i > 0) message += " ";
            message += cmd.args[i];
        }
        do_write("You say: " + message + "\r\n> ");
        return;
    }

    if (cmd.verb == "look") {
        do_write("You see nothing but the void of space.\r\n> ");
        return;
    }

    if (cmd.verb == "help") {
        do_write("Commands: look, say <msg>, help, quit\r\n> ");
        return;
    }

    do_write("Unknown command: " + cmd.verb + "\r\n> ");
}

void Session::do_write(const std::string& message)
{
    auto self = shared_from_this();
    auto buf = std::make_shared<std::string>(message);
    boost::asio::async_write(*socket_,
        boost::asio::buffer(*buf),
        [this, self, buf](const boost::system::error_code& ec, std::size_t) {
            if (ec) {
                std::cerr << "Write error: " << ec.message() << std::endl;
            }
        });
}

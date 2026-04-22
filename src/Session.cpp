#include "Session.h"
#include "Server.h"
#include "CommandParser.h"
#include "CommandDispatcher.h"
#include <iostream>

using namespace boost::asio;

Session::Session(boost::asio::io_context& io_context, Server& server)
    : socket_(io_context), server_(server)
{
}

Session::~Session()
{
    std::cout << "Session destroyed" << std::endl;
}

ip::tcp::socket& Session::socket()
{
    return socket_;
}

void Session::start()
{
    server_.game_.player_joins_game(player_);
    do_read();
}

void Session::do_read()
{
    auto self(shared_from_this());
    socket_.async_read_some(buffer(data_, max_length),
        [this, self](const boost::system::error_code& error, size_t bytes_transferred)
        {
            if (!error)
            {
                std::string message(data_, bytes_transferred);
                process_message(message);
                do_read();
            }
            else
            {
                server_.remove_session(self);
            }
        });
}

void Session::do_write(const std::string& message)
{
    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(message), 
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (ec)
            {
                server_.remove_session(self);
            }
        });
}

void Session::process_message(const std::string& message)
{
    CommandParser parser;
    ParsedCommand command = parser.parse(message);

    CommandDispatcher& dispatcher = server_.get_command_dispatcher();
    std::string response = dispatcher.dispatch(*this, command);

    do_write(response);
}

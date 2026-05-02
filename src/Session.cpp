#include "Session.h"
#include "Server.h"
#include "CommandParser.h"
#include "CommandDispatcher.h"
#include "Game.h"
#include <iostream>
#include <sstream>
#include <algorithm>

Session::Session(boost::asio::io_context& io_context, Server& server)
    : socket_(io_context), server_(server)
{
}

boost::asio::ip::tcp::socket& Session::socket()
{
    return socket_;
}

void Session::start()
{
    player_.name = "unnamed";
    boost::asio::async_read_until(socket_, buffer_, "\r",
        [this, self = shared_from_this()](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                read_complete(ec, length);
            } else {
                server_.remove_session(self);
                if (player_.currentRoom != nullptr) {
                    auto it = std::find_if(player_.currentRoom->sessions.begin(), player_.currentRoom->sessions.end(),
                        [this](const std::weak_ptr<Session>& wp) {
                            if (auto sp = wp.lock()) {
                                return sp.get() == this;
                            } else {
                                return false;
                            }
                        });
                    if (it != player_.currentRoom->sessions.end()) {
                        player_.currentRoom->sessions.erase(it);
                    }
                }

            }
        });
}

void Session::read_complete(boost::system::error_code ec, std::size_t length)
{
    std::string message(boost::asio::buffer_cast<const char*>(buffer_.data()), length);
    buffer_.consume(length);

    // Remove the carriage return character
    message.erase(std::remove(message.begin(), message.end(), '\r'), message.end());

    if (!message.empty()) {
        std::cout << "Received message: " << message << std::endl;
        process_command(message);
    }

    start(); // Start waiting for the next command
}

void Session::process_command(const std::string& message)
{
    CommandParser parser;
    ParsedCommand cmd = parser.parse(message);

    CommandDispatcher dispatcher;
    std::string response = dispatcher.dispatch(shared_from_this(), cmd);

    send(response);
}

void Session::send(const std::string& message)
{
    boost::asio::async_write(socket_, boost::asio::buffer(message), [](boost::system::error_code ec, std::size_t /*length*/) {
        if (ec) {
            std::cerr << "Error sending message: " << ec.message() << std::endl;
        }
    });
}

void Session::join_game(Room* room)
{
    if (player_.currentRoom != nullptr) {
        //Remove the player from the current room's session list
        auto it = std::find_if(player_.currentRoom->sessions.begin(), player_.currentRoom->sessions.end(),
            [this](const std::weak_ptr<Session>& wp) {
                if (auto sp = wp.lock()) {
                    return sp.get() == this;
                } else {
                    return false;
                }
            });
        if (it != player_.currentRoom->sessions.end()) {
            player_.currentRoom->sessions.erase(it);
        }
    }
    player_.currentRoom = room;
    player_.currentRoom->sessions.push_back(weak_from_this());
}

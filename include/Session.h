#pragma once

#include <boost/asio.hpp>
#include <string>
#include <memory>
#include "CommandDispatcher.h"

using boost::asio::ip::tcp;

struct Player
{
    std::string name = "Nameless";
};

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(std::shared_ptr<tcp::socket> socket);
    void start();
    void disconnect();

private:
    void do_read();
    void do_write(const std::string& msg);

    std::shared_ptr<tcp::socket> socket_;
    boost::asio::streambuf read_buffer_;
    bool disconnecting_ = false;
    CommandDispatcher command_dispatcher_;

    Player player_;
};

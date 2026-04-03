#pragma once

#include <boost/asio.hpp>
#include <memory>
#include <string>
#include "CommandParser.h"
#include "CommandDispatcher.h"

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
public:
    explicit Session(std::shared_ptr<tcp::socket> socket);
    void start();
    void disconnect();

private:
    void do_read();
    void do_write(const std::string& msg);

    std::shared_ptr<tcp::socket> socket_;
    char read_buffer_[1024];
    CommandParser parser_;
    CommandDispatcher dispatcher_;
    bool disconnecting_ = false;
};

#pragma once

#include <boost/asio.hpp>
#include <memory>
#include <array>
#include <string>

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
public:
    Session(std::shared_ptr<tcp::socket> socket);
    void start();

private:
    void do_read();
    void do_write(const std::string& message);
    void handle_input(const std::string& input);

    std::shared_ptr<tcp::socket> socket_;
    std::array<char, 1024> read_buffer_;
};

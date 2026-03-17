#include "Server.h"

Server::Server(boost::asio::io_context& io_context, unsigned short port)
    : io_context_(io_context),
      acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
{
}

void Server::start_accept()
{
    auto socket = std::make_shared<tcp::socket>(io_context_);
    acceptor_.async_accept(*socket,
        [this, socket](const boost::system::error_code& error) {
            handle_accept(socket, error);
        });
}

void Server::handle_accept(std::shared_ptr<tcp::socket> socket,
                           const boost::system::error_code& error)
{
    if (!error) {
        std::string welcome = "Welcome to MUD-Space!\r\n";
        boost::asio::async_write(*socket,
            boost::asio::buffer(welcome),
            [socket](const boost::system::error_code&, std::size_t) {
                // connection handed off, will expand with Session later
            });
        std::cout << "New connection from: "
                  << socket->remote_endpoint().address().to_string()
                  << std::endl;
    }

    start_accept();
}

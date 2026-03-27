#include "Server.h"
#include "Session.h"

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
        std::make_shared<Session>(std::move(socket))->start();
    }

    start_accept();
}
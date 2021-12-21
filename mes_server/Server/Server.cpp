#include "Server.h"



Server::Server(short port)
        : acceptor_(io_context_, tcp::endpoint(tcp::v4(), port))
{
    start_accept();
}

void Server::run()
{
    io_context_.run();
    CheckDB();
}

void Server::start_accept()
{
    auto new_connection = new Connection(io_context_);
    acceptor_.async_accept(new_connection->socket(),
                           boost::bind(&Server::handle_accept,
                                       this,
                                       new_connection,
                                       boost::asio::placeholders::error));
}

void Server::handle_accept(Connection* new_connection,
                   const boost::system::error_code& error)
{
    if (!error)
    {
        new_connection->start();
    }
    else
    {
        delete new_connection;
    }

    start_accept();
}


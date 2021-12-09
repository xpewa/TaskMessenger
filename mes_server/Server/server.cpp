
#include <cstdlib>
#include <iostream>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
#include <../Connection/Conneciton.h>

using boost::asio::ip::tcp;

class Server
{
public:
    Server(short port)
            : acceptor_(io_context_, tcp::endpoint(tcp::v4(), port))
    {
        start_accept();
    }

    void run()
    {
        io_context_.run();
    }

private:
    void start_accept()
    {
        Connection* new_connection = new Connection(io_context_);
        acceptor_.async_accept(new_connection->socket(),
                               boost::bind(&Server::handle_accept,
                                           this,
                                           new_connection,
                                           boost::asio::placeholders::error));
    }

    void handle_accept(Connection* new_connection,
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

private:
    boost::asio::io_context io_context_;
    tcp::acceptor acceptor_;
};

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: server <port>\n";
            return 1;
        }

        Server s(std::atoi(argv[1]));

        s.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}

#include <cstdlib>
#include <string>
#include <iostream>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
#include "UserDBManager.h"
#include "TaskDBManager.h"

using boost::asio::ip::tcp;

class Connection
{
public:
    Connection(boost::asio::io_context& io_context)
            : socket_(io_context)
    {
    }

    tcp::socket& socket()
    {
        return socket_;
    }

    void start()
    {
        socket_.async_read_some(boost::asio::buffer(recieved_, max_length),
                                boost::bind(&Connection::handle_read, this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred));
    }

private:
    std::string readUntil(char until, const char* arr, int &counter)
    {
        std::string result = "";
        while (arr[counter] != ':') {
            result += recieved_[counter++];
        }

        return result;
    }

    void Process()
    {
        UserDBManager UDBM;
        TaskDBManager TDBM;

        int i = 0;
        request = readUntil(':', recieved_, i);

        ++i;

        if (request == "authorization") {
            username = readUntil('\r', recieved_, i);

            User usr(username);
            UDBM.add_user(usr);
        }
        else {
            if (request == "add") {
                ++i;
                username = readUntil(':', recieved_, i);
                head = readUntil(':', recieved_, i);
                body = readUntil('\r', recieved_, i);
                int id = UDBM.search_user(username).id;
                Task tsk(head, body, id);
                TDBM.add_task(tsk);
            }
            else {
                if (request == "get") {
                    vector <Task> tasks;
                    username = readUntil('\r', recieved_, i);
                    int id = UDBM.search_user(username).id;
                    tasks = TDBM.get_user_tasks(id);
                }
            }
        }
    }

    void handle_read(const boost::system::error_code& error,
                     size_t bytes_transferred)
    {
        Process();
        if (!error)
        {
            boost::asio::async_write(socket_,
                                     boost::asio::buffer(recieved_, bytes_transferred),
                                     boost::bind(&Connection::handle_write, this,
                                                 boost::asio::placeholders::error));
        }
        else
        {
            delete this;
        }
    }

    void handle_write(const boost::system::error_code& error)
    {
        if (!error)
        {
            socket_.async_read_some(boost::asio::buffer(recieved_, max_length),
                                    boost::bind(&Connection::handle_read, this,
                                                boost::asio::placeholders::error,
                                                boost::asio::placeholders::bytes_transferred));
        }
        else
        {
            delete this;
        }
    }

private:
    tcp::socket socket_;
    enum { max_length = 10000 };
    char recieved_[max_length];
    std::string username, head, body, request;
};

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
            std::cerr << "Usage: async_tcp_echo_server <port>\n";
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

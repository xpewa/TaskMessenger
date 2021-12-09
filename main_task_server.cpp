
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
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
        while (arr[counter] != until) {
            result += recieved_[counter++];
        }

        return result;
    }

    void static CopyFromStringToCharArray(const std::string& str, size_t str_size, char* arr)
    {
        for (size_t counter = 0; counter < str_size; ++counter)
        {
            arr[counter] = str[counter];
        }
    }

    std::string PrepareStringTasksResponse(std::vector<Task> arr, UserDBManager& UDBM)
    {
        std::string result = "";
        size_t size = arr.size();
        for (size_t counter = 0; counter < size - 1; ++counter)
        {
            result += std::to_string(arr[counter].id) + ":" + arr[counter].head + ":" + UDBM.get_user(arr[counter].assigner_id).login
                    + ":" + UDBM.get_user(arr[counter].executor_id).login + ":";
        }
        result += std::to_string(arr[size - 1].id) + ":" + arr[size - 1].head + ":" + UDBM.get_user(arr[size - 1].assigner_id).login
                    + ":" + UDBM.get_user(arr[size - 1].executor_id).login;

        return result;
    }

    void EmptySendBuffer(char* arr)
    {
        for (size_t counter = 0; counter < max_length; ++counter)
        {
            arr[counter] = '\r';
        }
    }

    void Process()
    {
        UserDBManager UDBM;
        TaskDBManager TDBM;

        int i = 0;
        std::string request, username, head, assigner, executor;
        request = readUntil(':', recieved_, i);

        ++i;

        if (request == "authorization") {
            username = readUntil('\r', recieved_, i);

            User usr(username);
            UDBM.add_user(usr);
            int id = UDBM.search_user(username).id;
            to_send = username + ":" + std::to_string(id) + "\r" + "\n";
//            EmptySendBuffer(sent_);
            CopyFromStringToCharArray(to_send, to_send.size(), sent_);

            send_required = true;
        }
        else {
            if (request == "add") {
                head = readUntil(':', recieved_, i);
                ++i;
                assigner = readUntil(':', recieved_, i);
                ++i;
                executor = readUntil('\r', recieved_, i);
                int assigner_id = UDBM.search_user(assigner).id;
                int executor_id = UDBM.search_user(executor).id;
                Task tsk(head, assigner_id, executor_id);
                TDBM.add_task(tsk);

                send_required = false;
            }
            else {
                if (request == "get") {
                    vector <Task> tasks;
                    username = readUntil('\r', recieved_, i);
                    int id = UDBM.search_user(username).id;
                    tasks = TDBM.get_user_tasks(id);
                    to_send = std::to_string(tasks.size()) + ":"
                            + PrepareStringTasksResponse(tasks, UDBM)
                              + "\r" + "\n";
//                    EmptySendBuffer(sent_);
                    CopyFromStringToCharArray(to_send, to_send.size(), sent_);

                    send_required = true;
                }
            }
        }
    }

    void handle_read(const boost::system::error_code& error,
                     size_t bytes_transferred)
    {
        Process();
        if (send_required)
        {
            if (!error)
            {
                boost::asio::async_write(socket_,
                                         boost::asio::buffer(sent_, to_send.size()),
                                         boost::bind(&Connection::handle_write, this,
                                                     boost::asio::placeholders::error));
            }
            else
            {
                delete this;
            }
        }
        else
        {
            handle_write(error);
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
    char sent_[max_length];
    bool send_required;
    std::string to_send;
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
    CheckDB();
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

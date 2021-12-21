#include "Connection.h"

Connection::Connection(boost::asio::io_context& io_context)
        : socket_(io_context)
{
}

tcp::socket&  Connection::socket()
{
    return socket_;
}

void Connection::start()
{
    socket_.async_read_some(boost::asio::buffer(input_, max_length),
                            boost::bind(&Connection::handle_read, this,
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
}


void Connection::handle_read(const boost::system::error_code& error,
                 size_t bytes_transferred)
{
    MessageDBManager MDBM;
    int i = 0;
    stringstream input_stringstream(input_);
    std::getline(input_stringstream, request, ':');
    if (request == "get")
    {
        output_ = "";
        std::getline(input_stringstream, request, ':');
        int task_id = std::stoi(request);
        vector<Message> list_all_mes = MDBM.get_messages(task_id);
        output_ += to_string(list_all_mes.size());
        for (int i = 0; i < list_all_mes.size(); ++i)
        {
            output_ += ':';
            output_ += std::to_string(list_all_mes[i].from_id);
            output_ += ':';
            output_ += list_all_mes[i].text;
            output_ += "/r/n/r/n";
        }
        boost::asio::async_write(socket_,
                                 boost::asio::buffer(output_, bytes_transferred),
                                 boost::bind(&Connection::handle_write, this,
                                             boost::asio::placeholders::error));
    }
    else if (request == "add")
    {
        string new_text, task_id, from_id;
        std::getline(input_stringstream, new_text, ':');
        std::getline(input_stringstream, task_id, ':');
        std::getline(input_stringstream, from_id, ':');
        Message new_mes(new_text, std::stoi(task_id),
                        std::stoi(from_id));

        MDBM.add_message(new_mes);
    }
}

void Connection::handle_write(const boost::system::error_code& error)
{

    if (!error)
    {
        socket_.async_read_some(boost::asio::buffer(input_, max_length),
                                boost::bind(&Connection::handle_read, this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred));
    }
    else
    {
        delete this;
    }
}
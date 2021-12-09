

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "Connection.h"


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
        socket_.async_read_some(boost::asio::buffer(data_, max_length),
                                boost::bind(&Connection::handle_read, this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred));
    }

private:
    void handle_read(const boost::system::error_code& error,
                     size_t bytes_transferred)
    {
        MessageDBManager MDB;
        int i = 0;
        request = readUntil(':', input_, i);
        if (request == "get")
        {
            output_ = "";
            int task_id = std::stoi(readUntil(':', input_, i));
            vector<Message> list_all_mes = MDB.get_messages(task_id);
            output_ += to_string(list_all_mes.size());
            for (i = 0; i < list_all_mes.size(), i++)
            {
                Message temp_mes = list_all_mes[i];
                output_ += ':';
                output_ += temp_mes.GetUser();
                output_ += ':';
                output_ += temp_mes.GetMessage();
            }
            boost::asio::async_write(socket_,
                                     boost::asio::buffer(output_, bytes_transferred),
                                     boost::bind(&Connection::handle_write, this,
                                                 boost::asio::placeholders::error));
        }
        else if (request == "add")
        {
            Message new_message;
            new_message.setText(readUntil(':', input_, i));
            new_message.setWorker(readUntil(':', input_, i));
            new_message.setAssigner(readUntil(':', input_, i));
            MDB.add_message(new_massage);
        }
    }

    std::string readUntil(char until, const char* arr, int &counter)
    {
        std::string result = "";
        while (arr[counter] != until) {
            result += recieved_[counter++];
        }

        return result;
    }



    void add_message_to_bd()
    {

    }

    void handle_write(const boost::system::error_code& error)
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
//            delete this;
        }
    }
};
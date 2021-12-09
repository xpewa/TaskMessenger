
#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H


#include <array>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <deque>

using boost::asio::ip::tcp;

class Connection {
public:
    Connection(boost::asio::io_context& io_context)
            : socket_(io_context)
    {
    }
public:

    typedef boost::system::error_code error_code;
    typedef std::shared_ptr<Connection> ptr;


    void start(const boost::system::error_code& error);

//    void on_message(std::array<char, MAX_IP_PACK_SIZE>& msg);

private:


    void name_handler(const boost::system::error_code& error);

    void read_handler(const boost::system::error_code& error);

    void write_handler(const boost::system::error_code& error);

private:
    tcp::socket socket_;
    enum { max_length = 1024 };
    char data_[max_length];
    boost::asio::streambuf read_msg_;
    std::deque<std::string> write_msgs_;
};

#endif //SERVER_CONNECTION_H

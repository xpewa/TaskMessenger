
#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include "../../DB/MessageDBManager.h"
#include <iostream>

using boost::asio::ip::tcp;

class Connection {
public:
    Connection(boost::asio::io_context& io_context);

    typedef boost::system::error_code error_code;
    typedef std::shared_ptr<Connection> ptr;
    tcp::socket&  socket();


    void start();



private:
    void handle_read(const boost::system::error_code& error,
                     size_t bytes_transferred);

    void handle_write(const boost::system::error_code& error);

    tcp::socket socket_;
    enum { max_length = 1024 };
    std::string input_;
    std::string output_;
    std::string request;

//    boost::asio::streambuf read_msg_;
};

#endif //SERVER_CONNECTION_H

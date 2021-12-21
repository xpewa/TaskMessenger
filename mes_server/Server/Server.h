#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H


#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include "../Connection/Connection.h"
#include "../../DB/MessageDBManager.h"

#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Server {
public:
    explicit Server(short port);
    void run();
private:
    void start_accept();
    void handle_accept(Connection* new_connection,
                       const boost::system::error_code& error);
    boost::asio::io_context io_context_;
    tcp::acceptor acceptor_;
//    std::map<int, std::shared_ptr<Connection>> client_collection;
};



#endif //SERVER_SERVER_H

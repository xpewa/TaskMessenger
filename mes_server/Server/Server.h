#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H


#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include "../Connection/Connection.h"
#include "../../DB/MessageDBManager.h"

using boost::asio::ip::tcp;

class Server {
public:
    void run();
private:

    boost::asio::io_context io_context_;
    tcp::acceptor acceptor_;
    std::map<int, std::shared_ptr<Connection>> client_collection;
};



#endif //SERVER_SERVER_H

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H


#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include "../Connection/Connection.h"
//#include "../BD/MessageDBManager.h"

using namespace boost::asio;

using boost::asio::ip::tcp;

class Server {
private:

    void run();
    boost::asio::io_context io_context_;
    tcp::acceptor acceptor_;
    std::map<int, std::shared_ptr<Connection>> client_collection;
};



#endif //SERVER_SERVER_H

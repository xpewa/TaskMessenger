#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H




#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include "../Connection/Connection.h"

using namespace boost::asio;

using boost::asio::ip::tcp;

class Server: public std::enable_shared_from_this<Server>  {
public:
    explicit Server(boost::asio::io_service& io_service);
    Server(boost::asio::io_service io_service_,
           boost::asio::io_service::strand& strand,
           const tcp::endpoint& endpoint);
    typedef std::shared_ptr<Server> ptr;

private:

    void run();
    boost::asio::io_service &io_service_;
    tcp::acceptor acceptor_;
    std::map<int, std::shared_ptr<Connection>> client_collection;
};



#endif //SERVER_SERVER_H
